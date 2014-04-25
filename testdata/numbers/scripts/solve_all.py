import os
import subprocess

f_list = os.listdir("../")

for f_in in f_list:
    if f_in.endswith(".in"):
        f_out = f_in.rsplit(".", 1)[0]+".sol"
        print(f_in.rsplit(".",1)[0])
        subprocess.call("./numbers < ../"+f_in+" > ../"+f_out, shell=True)
