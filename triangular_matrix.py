import random
import copy

class matrix(list):
    def __init__(self, size):
        col = 0;
        row = 0;
        while row < size:
            self.append(list());
            col = 0;
            while col < size:
                self[row].append (0.0);
                col += 1;
            row += 1;

    def __repr__(self):
        size = len(self);
        buff = "";
        for row in range(size):
            for col in range(size):
                buff += " %9f "%(self[row][col])
            buff += "\n";
        return buff;

    def __switch_line(self, l1, l2):
        size = len(self);
        tmp = self[l1];
        self[l1] = self[l2];
        self[l2] = tmp;
    def __line_multi(self, line, x):
        ret = copy.deepcopy(self[line]);
        for i in range(len(self)):
            ret[i] *= x;
        return ret;

    def __line_add(self, line, x):
        ret = copy.deepcopy(self[line]);
        for i in range(len(self)):
            ret[i] += x[i];
        return ret;

    def __line_sub(self, line, x):
        ret = copy.deepcopy(self[line]);
        for i in range(len(self)):
            ret[i] -= x[i];
        return ret;

    def __trianglize(self):
        tmp = copy.deepcopy(self);
        size = len(self);
        ratio = 1;
        for i in range(size - 1):
            if tmp[i][i] == 0:
                for x in range(i + 1, size):
                    if tmp[x][i] != 0:
                        tmp.__switch_line(i, x);
                        break;
                if tmp[i][i] == 0:
                    continue;
            for j in range(i + 1, size):
                ratio = tmp[j][i] / tmp[i][i];
                tmp_line = tmp.__line_multi(i, ratio);
                tmp[j] = tmp.__line_sub(j, tmp_line);
        return tmp;



    def det(self):
        ret = 1;
        tmp = self.__trianglize();
        for i in range(len(self)):
            ret *= tmp[i][i];
        return ret;


def create_rand_matrix(size):
    ret = matrix(size);
    for row in range(size):
        for col in range(size):
            ret[row][col] = float(random.randint(0, 20)); 
    return ret





    

m1 = create_rand_matrix(20);
print m1;
print int(m1.det());
