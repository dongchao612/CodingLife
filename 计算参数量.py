import torch.nn as  nn
import torch
from thop import profile


class Net(nn.Module):
    def __init__(self, input_channels, output_channels, kernel_size):
        super(Net, self).__init__()
        self.c = nn.Conv2d(input_channels, output_channels, kernel_size=kernel_size, stride=1)

    def forward(self, x):
        return self.c(x)


class SepConv(nn.Module):
    def __init__(self, in_channel, out_channel, kernel_size, stride, padding):
        super(SepConv, self).__init__()
        self.conv1 = nn.Conv2d(in_channel, in_channel, kernel_size, stride, padding, groups=in_channel)
        self.conv2 = nn.Conv2d(in_channel, out_channel, kernel_size=(1, 1), stride=(1, 1), padding=0)

    def forward(self, input):
        x = self.conv1(input)
        x = self.conv2(x)

        return x


# print('Total params: %.2fM' % (sum(p.numel() for p in net.parameters())/1000000.0))
if __name__ == '__main__':
    from mobilenet1 import DepthSeparableConv2d
    x = torch.randn(1, 3, 224, 224)
    net = Net(3, 64, 3)
    net1 = SepConv(3, 64, 3, 1, 0)
    net2=DepthSeparableConv2d(3, 64, 3)


    print(net.forward(x).shape)
    print(net1.forward(x).shape)
    print(net2.forward(x).shape)

    print('Total params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    print('Total params: %fM' % (sum(p.numel() for p in net1.parameters()) / 1000000.0))
    print('Total params: %fM' % (sum(p.numel() for p in net2.parameters()) / 1000000.0))
