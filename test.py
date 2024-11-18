import os
import subprocess

correct_folder = "correct"
wrong_folder = "wrong"
choose_folders = ["correct", "wrong", "phase1"]

for choose_folder in choose_folders:
    input_folder = "testcase/input/" +  choose_folder 
    output_folder = "testcase/output/" + choose_folder 

    os.makedirs(output_folder, exist_ok=True)

    for filename in os.listdir(input_folder):
        if filename.endswith(".spl"):
            input_file = os.path.join(input_folder, filename)
            output_file = os.path.join(output_folder, filename.replace(".spl", ".out"))
            
            with open(output_file, "w") as out_file:
                subprocess.run(["./splc", input_file], stdout=out_file, stderr=out_file)

print("所有文件已处理，输出已保存到 'output' 文件夹中。\n")
