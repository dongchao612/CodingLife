import torch
import torch.nn as  nn

# 卷积块，由三部分组成，卷积BatchNorm核激活函数（RelU）组成
from thop import profile
from timm.models.layers.helpers import make_divisible


class ConvBNReLU(nn.Module):

    def __init__(self, input_channels, output_channels, kernel_size, stride, **kwargs):
        super(ConvBNReLU, self).__init__()
        self.conv = nn.Conv2d(input_channels, output_channels, kernel_size, stride, **kwargs)
        self.bn = nn.BatchNorm2d(output_channels)
        self.relu = nn.ReLU(inplace=True)

    def forward(self, x):
        x = self.conv(x)
        x = self.bn(x)
        x = self.relu(x)
        return x


# 深度可分离卷积块，由两部分组成，1.单核dw卷积，2.逐点卷积
class DepthSeparableConv2d(nn.Module):
    def __init__(self, in_channel, out_channel, kernel_size, **kwargs):
        super(DepthSeparableConv2d, self).__init__()
        ## DW卷积
        self.depthConv = nn.Sequential(
            nn.Conv2d(in_channel, in_channel, kernel_size, groups=in_channel, **kwargs),
            nn.BatchNorm2d(in_channel),
            nn.ReLU(inplace=True)
        )
        # 逐点卷积
        self.pointConv = nn.Sequential(
            nn.Conv2d(in_channel, out_channel, (1, 1)),
            nn.BatchNorm2d(out_channel),
            nn.ReLU(inplace=True)
        )

    def forward(self, x):
        x = self.depthConv(x)
        x = self.pointConv(x)
        return x


class SepConv(nn.Module):
    def __init__(self, in_channel, out_channel, kernel_size, stride, padding):
        super(SepConv, self).__init__()
        self.conv1 = nn.Conv2d(in_channel, in_channel, kernel_size, stride, padding, groups=in_channel)
        self.conv2 = nn.Conv2d(in_channel, out_channel, kernel_size=(1, 1), stride=(1, 1), padding=0)

    def forward(self, input):
        x = self.conv1(input)
        x = self.conv2(x)

        return x


class MobileNetV1(nn.Module):

    def __init__(self, in_channels=3, scale=1.0, num_classes=1000, **kwargs):
        super(MobileNetV1, self).__init__()

        input_channel = make_divisible(32 * scale)
        # 开始的一个卷积快用于映射特征
        self.conv1 = ConvBNReLU(in_channels, input_channel, 3, 2, padding=1, bias=False)
        # 深度可分离卷积参数设置
        # 输入通道、输出通道，stride
        depthSeparableConvSize = [
            # in out ,s, s
            [32, 64, 1],
            [64, 128, 2],
            [128, 256, 1],
            [256, 256, 1],
            [256, 512, 2],
        ]

        conv2 = []

        for i, o, s in depthSeparableConvSize:
            output_channel = make_divisible(o * scale)
            # 加入可分离深度卷积层
            conv2.append(SepConv(input_channel, output_channel, 3, stride=s, padding=1))
            input_channel = output_channel

        self.conv2 = nn.Sequential(*conv2)

        conv3 = []
        for i in range(5):
            # 加深度可分离卷积层，深度5
            conv3.append(SepConv(input_channel, input_channel, 3, stride=1, padding=1))
        self.conv3 = nn.Sequential(*conv3)

        last_channel = make_divisible(1024 * scale)
        # 加入深度可分离卷积，深度1
        self.conv4 = nn.Sequential(
            SepConv(input_channel, last_channel, 3, stride=2, padding=1),
            SepConv(last_channel, last_channel, 3, stride=2, padding=1)
        )
        # 池化层
        self.avgpool = nn.AdaptiveAvgPool2d(1)
        # 线性分类层
        self.fc = nn.Sequential(
            nn.Linear(last_channel, num_classes),
            nn.Softmax(),
        )

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.avgpool(x)
        # 将三维图像展平为二维分类特征
        x = torch.flatten(x, 1)
        # print(len(x[0]))
        x = self.fc(x)
        return x


if __name__ == '__main__':
    x = torch.randn(1, 3, 224, 224)
    net = MobileNetV1()
    print(net.forward(x).shape)
    print('Total params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))

