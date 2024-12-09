import os
import subprocess

phase = '2'

def process_files(input_base_folder):
    # 构建output文件夹的根目录
    output_base_folder = "testcase/output"
    
    # 遍历input文件夹及其所有子文件夹
    for root, dirs, files in os.walk(input_base_folder):
        for filename in files:
            if filename.endswith(".spl"):
                # 输入文件路径
                input_file = os.path.join(root, filename)
                
                # 计算输出文件夹路径，保持相对路径
                relative_path = os.path.relpath(root, input_base_folder)
                output_folder = os.path.join(output_base_folder, relative_path)
                
                # 确保输出文件夹存在
                os.makedirs(output_folder, exist_ok=True)
                
                # 输出文件路径
                output_file = os.path.join(output_folder, filename.replace(".spl", ".out"))
                inter_file = os.path.join(output_folder, filename.replace(".spl", ".ir"))
                
                # 执行命令并将输出写入文件
                with open(output_file, "w") as out_file:
                    subprocess.run(["./splc", input_file, '2'], stdout=out_file, stderr=out_file)
                with open(inter_file, "w") as out_file:
                    subprocess.run(["./splc", input_file, '3'], stdout=out_file, stderr=out_file)
    
    print("所有文件已处理，输出已保存到 'output' 文件夹中。\n")

# 传入input文件夹的路径，调用函数
input_folder = "testcase/input"  # 传入实际的input文件夹路径
process_files(input_folder)
