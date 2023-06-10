import torch


if __name__ == '__main__':
    from torchvision.models import squeezenet1_0,squeezenet1_1
    net = squeezenet1_0()
    print('squeezenet1_0  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = squeezenet1_1()
    print('squeezenet1_1  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    print("*"*20)
    from torchvision.models import mnasnet0_5,mnasnet0_75,mnasnet1_0,mnasnet1_3
    net = mnasnet0_5()
    print('mnasnet0_5  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = mnasnet0_75()
    print('mnasnet0_75  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = mnasnet1_0()
    print('mnasnet1_0  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = mnasnet1_3()
    print('mnasnet1_3  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    print("*" * 20)
    from torchvision.models import mobilenet_v2, mobilenet_v3_small, mobilenet_v3_large
    net = mobilenet_v2()
    print('mobilenet_v2  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = mobilenet_v3_small()
    print('mobilenet_v3_small  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = mobilenet_v3_large()
    print('mobilenet_v3_large  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    print("*" * 20)
    from torchvision.models import shufflenet_v2_x0_5,shufflenet_v2_x1_0,shufflenet_v2_x1_5,shufflenet_v2_x2_0
    net = shufflenet_v2_x0_5()
    print('shufflenet_v2_x0_5  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = shufflenet_v2_x1_0()
    print('shufflenet_v2_x1_0  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = shufflenet_v2_x1_5()
    print('shufflenet_v2_x1_5  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    net = shufflenet_v2_x2_0()
    print('shufflenet_v2_x2_0  params: %fM' % (sum(p.numel() for p in net.parameters()) / 1000000.0))
    print("*" * 20)

