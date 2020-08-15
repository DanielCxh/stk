#!/usr/python3

import os
import time

# Global config.
TEMP_HEAD_FILE_PATH = './cpp_head_license_example.hpp'
SRC_FOLDER          = './src'

CRT_DATE = ''

SRC_FILE_SET = []

def get_head_ctx(path):
    if False == os.path.exists(path):
        print('[get_head_ctx]Template head file [%s] not exist, please check it!' % (path))
    else:
        pass

    fd = open(path)

    head_ctx = fd.read()

    fd.close()

    return head_ctx


def add_head_to_file(files, ctx):
    global CRT_DATE

    for f in files:
        if False == os.path.exists(str(f)):
            print('[add_head_to_file]Template head file [%s] not exist, please check it!' % (f))
        else:
            head_ctx = ctx

            fd = open(f, 'r+')

            file_ctx = ''

            flag = False
            lines = fd.readlines()

            for line in lines:
                if line.startswith('#ifndef') or line.startswith('#include'):
                    flag = True
                if True == flag:
                    file_ctx += line

            file = f.split('/')[-1]
            file_name = file.split('.')[0]

            head_ctx = head_ctx.replace('{FILE}', file)
            head_ctx = head_ctx.replace('{FILE_NAME}', file_name)
            head_ctx = head_ctx.replace('{YYYY-MM-DD}', CRT_DATE)

            tx = head_ctx + '\n' + file_ctx

            fd.seek(0)
            fd.write(tx)


            fd.close()

def find_file(path):
    for i in os.listdir(path):
        file_path = os.path.join(path, i)
        if os.path.isdir(file_path):
            find_file(file_path)
        else:
            if i.endswith('.cpp') or i.endswith('.cc') or i.endswith('.h') or i.endswith('.hpp'):
                SRC_FILE_SET.append(file_path)
            else:
                pass


def proc():
    global CRT_DATE
    CRT_DATE = time.strftime("%Y-%m-%d", time.localtime())
    find_file(SRC_FOLDER)
    head_ctx = get_head_ctx(TEMP_HEAD_FILE_PATH)
    add_head_to_file(SRC_FILE_SET, head_ctx)


if __name__ == '__main__':
    proc()
