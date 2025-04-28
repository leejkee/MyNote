import subprocess

# 可执行文件路径
executable = "sum/a.exe"  # 这里替换为你的可执行文件路径

# 执行30次
for i in range(1):
    # 使用subprocess运行程序
    result = subprocess.run([executable], capture_output=True, text=True)
    # 输出每次运行的结果
    print(f"Output of iteration {i + 1}: {result.stdout}")
