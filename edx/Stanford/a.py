import torch

x = torch.ones(5)  # input tensor
y = torch.zeros(3)  # expected output

w = torch.randn(5, 3, requires_grad=True)
b = torch.randn(3, requires_grad=True)
z = torch.matmul(x, w) + b

loss = torch.nn.functional.binary_cross_entropy_with_logits(z, y)
loss.backward()
print(f"Weight tensor: {w}")
print(f"Bias tensor: {b}")
print(f"Weight gradient: {w.grad}")
print(f"Bias gradient: {b.grad}")
print(f"Input gradient: {x.grad}")  # None, because x is not a leaf node
print(f"Loss value: {loss}")
print(f"Loss gradient function: {loss.grad_fn}")
print(f"Loss gradient: {loss.grad}")  # None, because loss is a scalar
print(f"Z gradient function: {z.grad_fn}")
print(f"Z requires gradient: {z.requires_grad}")
print(f"X requires gradient: {x.requires_grad}")
print(f"Y requires gradient: {y.requires_grad}")
print(f"W requires gradient: {w.requires_grad}")
print(f"B requires gradient: {b.requires_grad}")
print(f"Z requires gradient: {z.requires_grad}")
