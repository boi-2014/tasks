import os

subtask_dict = { "01" : "1",
                 "02" : "1",
                 "03" : "2",
                 "04" : "3",
                 "05" : "4" }

test_no = 1

for f in sorted(os.listdir("../")):
    if f.endswith(".in") and f.startswith("tinklas."):
        label = f.rsplit(".",2)[1]

        old_subtask = label[1]+label[2]
        new_subtask = subtask_dict[old_subtask]
        new_test = "{0:02d}".format(test_no)

        os.rename("../"+f, "../network."+new_test+"-"+new_subtask+".in")

        test_no = test_no+1
