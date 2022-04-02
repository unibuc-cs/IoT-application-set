from requests import post
from sys import argv
from time import sleep
from random import randint

IMG_W = 16
IMG_H = 9

def main():
    box_host = argv[1]
    box_port = argv[2]
    delay = int(argv[3])

    while True:
        try:
            img = gen_image()
            post(f"http://{box_host}:{box_port}/process", json=img)
        except Exception as e:
            print(e)
        sleep(delay)

def gen_image():
    img = []
    for i in range(IMG_H):
        img.append([])
        for j in range(IMG_W):
            img[i].append([randint(0, 255), randint(0, 255), randint(0, 255)])
    return img

if __name__ == '__main__':
    main()