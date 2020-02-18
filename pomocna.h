#ifndef pomocnaH
#define pomocnaH

using namespace std;

struct Tacka{
	int x;
	int y;
	Tacka(){
		this->x = 0;
		this->y = 0;
	}
	Tacka(int x,int y){
		this->x = x;
		this->y = y;
	}
};

bool operator<(Tacka A,Tacka B){
	if(A.x < B.x){
		return true;
	}
	if(A.x == B.x){
		return A.y < B.y;
	}
	return false;
}

bool operator==(Tacka A, Tacka B){
	if(A.x == B.x && A.y == B.y){
		return true;
	}

    return false;
}



struct Segment{
	Tacka start;
	Tacka end;
	Segment(){
		this->start = Tacka(-1,-1);
        this->end = Tacka(-1,-1);
	}
	Segment(Tacka A, Tacka B){
		this->start = A;
		this->end = B;

		if(B < A){
			swap(start,end);
		}


	}
};


bool operator==(Segment A, Segment B){
	double x_start_difference = abs(A.start.x - B.start.x);
	double y_start_difference = abs(A.start.y - B.start.y);
	double x_end_difference = abs(A.end.x - B.end.x);
	double y_end_difference = abs(A.end.y - B.end.y);
	return x_start_difference <= 20 && y_start_difference <= 20 && x_end_difference <= 20 && y_end_difference <= 20;
}


// SolarEnergyStation
struct SES{
	Tacka point;
	int index;
	SES(Tacka A,int i){
		this->point = A;
		this->index = i;
	}

};
// VoronoiEdge
struct VE{
	Segment segment;
	int first_neighbour;
	int second_neighbour;
	VE(Segment S, int i){
		this->segment = S;
		this->first_neighbour = i;
        this->second_neighbour = 0;
	}

};

// BorealisChangeStation
struct BCS{
	Tacka point;
	int first_neighbour;
	int second_neighbour;
	BCS(Tacka A, int first, int second){
		this->point = A;
		this->first_neighbour = first;
		this->second_neighbour = second;
	}

};




#endif
