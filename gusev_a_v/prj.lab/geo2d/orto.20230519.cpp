#include <iostream>
struct point {
	int x;
	int y;
};

class quad {
public:
	point center;
	int W = 0, H = 0;

	int getW() {
		return W;
	}

	int GetH() {
		return H;
	}

	void SetH(int hight) {
		H = hight;
	}

	void SetW(int width) {
		W = width;
	}

	void Scale(int n) {
		W /= n;
		H /= n;
	}

	//void Interset(quad qd) {
		//point temp;
	//}
};



int main() {
	quad q;
	q.SetH(12);
	q.SetW(6);
	q.Scale(2);
	//q.Interset(q);
	std::cout << q.getW()<<std::endl<<q.GetH();

	return 0;
}