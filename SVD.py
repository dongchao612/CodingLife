if __name__ == '__main__':
    from torchvision.models import resnet18

    net = resnet18()
    print(*list(net.children())[:1])
    import torch

    # C:\Users\32243\.cache\torch\hub\checkpoints
    orginal_dict = net.state_dict()  # 当前网络的权重字典。
    weight_dict = torch.load(r"C:\Users\32243\.cache\torch\hub\checkpoints\resnet18-f37072fd.pth")  # 读取的网络权重字典
    # print(weight_dict.keys())
    print("conv1.weight:",weight_dict["conv1.weight"][0][0])

    U, S, Vh = torch.linalg.svd(weight_dict["conv1.weight"][0][0], full_matrices=True)

    # V = Vh.mH
    print(U.shape)
    print(S.shape)
    print(Vh.shape)
    print(U @ Vh)
    print(S[0]*(U @ Vh))
