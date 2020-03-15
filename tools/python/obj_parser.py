import os


VERTEX = "v"
INDEX = "f"
ATTRIBUTE = "a"


def add_list(prefix, array):
    output = ''
    for index, elem in enumerate(array):
        output += f"{prefix} " if index % 3 == 0 or index == 0 else ""
        output += str(elem)
        output += "\n" if (index + 1) % 3 == 0 and index != 0 else " "
    output += "\n" if output[-1] != "\n" else ""
    return output


def add_attributes(array):
    output = ''
    for index, elem in enumerate(array):
        output += f"{ATTRIBUTE} {elem}\n"
    return output


def write_file(vertices=[], indices=[], attributes=[]):
    file = add_list(VERTEX, vertices)
    file += add_list(INDEX, indices)
    file += add_attributes(attributes)
    return file

if __name__=='__main__':
    v = [
      -0.5, 0.0, -0.5,
      0.5, 0.0, -0.5,
      0.5, 0.0,  0.5,
      -0.5, 0.0,  0.5,
    ]
    ind = list(range(1, 4+1))
    a = ["position"]
    with open('sandbox/assets/models/Plane.obj', 'w') as file:
        file.write(write_file(v, ind, a))
