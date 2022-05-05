import os
import sys

from testcase import testcase

proj_root = "../"


def patch_source(src="victim.c", index=0):
    src_path = os.path.join(proj_root, "executable", src)
    print(src_path)
    
    new_file = ""
    found_flag = False
    with open(src_path, "r") as victim_file:
        for line in victim_file.readlines():
            new_line = line.strip()
            # print(new_line)
            if "SECRET" in line and found_flag == False:
                new_line = "#define SECRET " + str(testcase[index])
                found_flag = True
            new_line += "\n"
            new_file += new_line

    with open(src_path, "w") as victim_file:
        victim_file.write(new_file)
    


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: {} <testcase num>".format(sys.argv[0]))
        os.exit(1)

    i = int(sys.argv[1])
    if i < 0 or i >= len(testcase):
        print("testcase num must be between 0 and ", len(testcase))

    patch_source(index=int(sys.argv[1]))