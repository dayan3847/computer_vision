import os


def fix_data(name: str):
    if not os.path.isfile(f'./{name}_fix.txt'):
        with open(f'./{name}.txt', 'r') as f:
            lines = f.readlines()
        # print('lines:', lines)
        lines_fixed = [' '.join(line.split()) + '\n' for line in lines]
        # print('lines_fixed:', lines_fixed)
        with open(f'./{name}_fix.txt', 'w') as f:
            f.writelines(lines_fixed)


if __name__ == '__main__':
    fix_data('original_corners')
    fix_data('iK_original_corners')
