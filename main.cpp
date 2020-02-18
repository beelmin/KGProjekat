//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
	center = Tacka(310,225);
	Image1->Canvas->Brush->Color = clRed;
	Image1->Canvas->Ellipse(center.x-4,center.y-4,center.x+4,center.y+4);
	earth_radius = 75;
	mars_radius = 2*earth_radius;
	jupiter_radius = 3*earth_radius -5;
	Image1->Canvas->Brush->Style = bsClear;
	Image1->Canvas->Ellipse(center.x-earth_radius,center.y-earth_radius,center.x+earth_radius,center.y+earth_radius);
	Image1->Canvas->Ellipse(center.x-mars_radius,center.y-mars_radius,center.x+mars_radius,center.y+mars_radius);
	Image1->Canvas->Ellipse(center.x-jupiter_radius,center.y-jupiter_radius,center.x+jupiter_radius,center.y+jupiter_radius);
	earth = Tacka(-1,-1);
	mars = Tacka(-1,-1);
	ses_index = 1;

}
//---------------------------------------------------------------------------

double TForm4::orientation_of_points(Tacka A, Tacka B, Tacka C){
	double a1 = B.x - A.x;
	double a2 = B.y - A.y;
	double b1 = C.x - A.x;
	double b2 = C.y - A.y;

	double result = a1*b2 - a2*b1;
	if(result < 0) {  // suprotno smjeru
		return 1;
	}else if(result == 0) {
		return 0;
	}else if(result > 0) {   // u smjeru
		return -1;
	}
}
void __fastcall TForm4::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(RadioButton2->Checked){	// dodajemo Zemlju
		if(earth.x != -1){
			ShowMessage("Vec ste odabrali Zemlju!");
			return;
		}
		if(abs(get_distance(Tacka(X,Y),center) - earth_radius) > 2){
			ShowMessage("Odabirete tacku na kruznici");
			return;
		}

		Image1->Canvas->Brush->Style = bsClear;
		earth = Tacka(X,Y);
		Image1->Canvas->Brush->Color = clBlue;
		Image1->Canvas->Ellipse(X-4,Y-4,X+4,Y+4);
		if(earth.x != -1 && mars.x != -1){
			Image1->Canvas->MoveTo(earth.x,earth.y);
			Image1->Canvas->LineTo(mars.x,mars.y);
		}
	}else if(RadioButton3->Checked){    // dodajemo Mars
	   if(mars.x != -1){
			ShowMessage("Vec ste odabrali Mars!");
			return;
	   }
	   if(abs(get_distance(Tacka(X,Y),center) - mars_radius) > 2){
			ShowMessage("Odabirete tacku na kruznici");
			return;
		}
	   Image1->Canvas->Brush->Style = bsClear;
	   mars = Tacka(X,Y);
	   Image1->Canvas->Brush->Color = clFuchsia;
	   Image1->Canvas->Ellipse(X-4,Y-4,X+4,Y+4);
       if(earth.x != -1 && mars.x != -1){
			Image1->Canvas->MoveTo(earth.x,earth.y);
			Image1->Canvas->LineTo(mars.x,mars.y);
	   }
	}else if(RadioButton4->Checked){
		if(get_distance(Tacka(X,Y),center) > jupiter_radius){
			ShowMessage("Izasli ste izvan dozvoljenog opsega");
            return;
		}
		Image1->Canvas->Brush->Style = bsClear;
		Image1->Canvas->Brush->Color = clBlack;
		Image1->Canvas->Ellipse(X-4,Y-4,X+4,Y+4);
		stations.push_back(SES(Tacka(X,Y),ses_index));

		TLabel *label = new TLabel(this);
		label->Parent = this;
		label->Height = 20;
		label->Width = 20;
		//edit->Text = ses_index;
		label->Caption = ses_index;
		label->Visible = true;
		label->Left = X-5;
		label->Top = Y-5;

		ses_index++;
	}

}
//---------------------------------------------------------------------------



double TForm4::get_distance(Tacka A, Tacka B){
	return sqrt((B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y));
}

bool TForm4::intersect_segment(Segment A, Segment B){
	int result1 = orientation_of_points(A.start,A.end,B.start);
	int result2 = orientation_of_points(A.start,A.end,B.end);
	int result3 = orientation_of_points(B.start,B.end,A.start);
	int result4 = orientation_of_points(B.start,B.end,A.end);


	bool sijeku_se = false;

	if(result1 != result2 && result3 != result4) {
		sijeku_se = true;
	}

	if(result1 == 0 && point_on_segment(A.start,A.end,B.start)){
		sijeku_se = true;
	}
	if(result2 == 0 && point_on_segment(A.start,A.end,B.end)) {
		sijeku_se = true;
	}
	if(result3 == 0 && point_on_segment(B.start,B.end,A.start)) {
		sijeku_se = true;
	}
	if(result4 == 0 && point_on_segment(B.start,B.end,A.end)) {
		sijeku_se = true;
	}

	if(sijeku_se){
		return true;
	}

	return false;

}



bool TForm4::point_on_segment(Tacka A, Tacka B, Tacka C) {
	double AC = (C.x-A.x)*(C.x-A.x) + (C.y-A.y)* (C.y-A.y);
	double CB =(B.x-C.x)*(B.x-C.x) + (B.y-C.y)* (B.y-C.y);
	double AB = (B.x-A.x)*(B.x-A.x) + (B.y-A.y)* (B.y-A.y);

	return AC + CB == AB;
}


Tacka TForm4::intersection_point(Segment A, Segment B){
	// segment A = AB , A = start, B = end
	// Line AB represented as a1x + b1y = c1
	double a1 = A.end.y - A.start.y;
	double b1 = A.start.x - A.end.x;
	double c1 = a1*(A.start.x) + b1*(A.start.y);

	double a2 = B.end.y - B.start.y;
	double b2 = B.start.x - B.end.x;
	double c2 = a2*(B.start.x) + b2*(B.start.y);

	double determinant = a1*b2 - a2*b1;

	// ako je determinant == 0, onda su paralelni, ali mi zovemo f-ju kad vec znamo da se sijeku
	// i treba nam tacka presjeka


	double x = (b2*c1 - b1*c2)/determinant;
	double y = (a1*c2 - a2*c1)/determinant;

	return Tacka(x,y);
}


Segment TForm4::perpendicular_bisector(Segment S){

	Tacka A = S.start;
	Tacka B = S.end;

	Tacka midpoint((A.x+B.x)/2, (A.y+B.y)/2);
	double x1,x2,y1,y2;
	double shift = 20;

	if(A.x == B.x){
		x1 = midpoint.x - shift;
		y1 = midpoint.y;
		x2 = midpoint.x + shift;
		y2 = midpoint.y;

	}else if(A.y == B.y){
		x1 = midpoint.x;
		y1 = midpoint.y-shift;
		x2 = midpoint.x;
		y2 = midpoint.y+shift;
	}else{
        double slope = (B.y - A.y) / double((B.x - A.x));
		slope = -1 / slope;
		// y = mx + b;
		double m = slope;
		double b = midpoint.y - m * midpoint.x;


		x1 = midpoint.x-shift;
		y1 = m*x1+b;
		x2 = midpoint.x+shift;
		y2 = m*x2+b;

	}

	return Segment(Tacka(x1,y1),Tacka(x2,y2));
}

Segment TForm4::increase_segment_length(Segment S){

	Tacka A = S.start;
	Tacka B = S.end;

	double x1,x2,y1,y2;
	if(A.x != B.x){
		double m = (B.y - A.y) / double((B.x - A.x));
		double b = A.y - m * A.x;

		// y = mx + b;

		x1 = -500;
		y1 = m*x1 + b;

		x2 = Image1->Width + 500;
		y2 = m*x2 + b;

	}else{
		x1 = A.x;
		y1 = -500;
		x2 = A.x;
		y2 = Image1->Height + 500;
	}

	return Segment(Tacka(x1,y1),Tacka(x2,y2));
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

bool TForm4::compare(BCS A, BCS B){
	return A.point < B.point;
}


void __fastcall TForm4::Button3Click(TObject *Sender)
{

	for(int i = 0; i < stations.size(); i++){
		vector<Segment>convex_hull = {Segment(Tacka(3,3),Tacka(Image1->Width-3,3)),
										 Segment(Tacka(3,3),Tacka(3,Image1->Height-3)),
										 Segment(Tacka(3,Image1->Height-3),Tacka(Image1->Width-3,Image1->Height-3)),
										 Segment(Tacka(Image1->Width-3,3),Tacka(Image1->Width-3,Image1->Height-3))};

		index = i;
		for(int j = 0; j < stations.size();j++){
			if(i != j){
				Segment pb(perpendicular_bisector(Segment(stations[i].point,stations[j].point)));
				intersection_convex_hull_and_segment(convex_hull,pb);
			}
		}

		Image1->Canvas->Pen->Color = clRed;
		for(int j = 0; j < convex_hull.size(); j++){
			int x1 = convex_hull[j].start.x;
			int x2 = convex_hull[j].end.x;
			bool exist = false;
			for(int k = 0; k < voronoi_edges.size(); k++){
				if(convex_hull[j] == voronoi_edges[k].segment){
					exist = true;
					voronoi_edges[k].second_neighbour = stations[i].index;
					break;
				}

			}
			if(!exist){
                voronoi_edges.push_back(VE(convex_hull[j],stations[i].index));
			}

		}

	}


	for(int i = 0; i < voronoi_edges.size(); i++){
		Image1->Canvas->MoveTo(voronoi_edges[i].segment.start.x,voronoi_edges[i].segment.start.y);
		Image1->Canvas->LineTo(voronoi_edges[i].segment.end.x,voronoi_edges[i].segment.end.y);
	}


}
//---------------------------------------------------------------------------

void TForm4::intersection_convex_hull_and_segment(vector<Segment> &convex_hull, Segment pb){

	Segment pb1 = increase_segment_length(pb);
	vector<Tacka>intersection_points;
	for(int i = 0; i < convex_hull.size();i++){
		if(intersect_segment(convex_hull[i],pb1)){
			intersection_points.push_back(intersection_point(convex_hull[i],pb1));
		}
	}

	vector<Tacka>points_of_new_convex_hull;
	if(intersection_points.size() == 2){
		Segment new_segment(intersection_points[0],intersection_points[1]);
		int orientation = orientation_of_points(new_segment.start,new_segment.end,stations[index].point);
		for(int i = 0; i < convex_hull.size(); i++){
			if(orientation_of_points(new_segment.start,new_segment.end,convex_hull[i].start) == orientation){
				points_of_new_convex_hull.push_back(convex_hull[i].start);
			}
			if(orientation_of_points(new_segment.start,new_segment.end,convex_hull[i].end) == orientation){
			   points_of_new_convex_hull.push_back(convex_hull[i].end);
			}
		}

		points_of_new_convex_hull.push_back(new_segment.start);
		points_of_new_convex_hull.push_back(new_segment.end);

		jarvis_march(convex_hull,points_of_new_convex_hull);

	}
}


int TForm4::distance(Tacka A, Tacka B, Tacka C){
	double ABx = B.x - A.x;
	double ABy = B.y - A.y;
	double ACx = C.x - A.x;
	double ACy = C.y - A.y;

    double distanceAB = sqrt(ABx*ABx + ABy*ABy);
    double distanceAC = sqrt(ACx*ACx + ACy*ACy);
    if(distanceAB < distanceAC) {
        return -1;
    }else if(distanceAB == distanceAC) {
        return 0;
	}else {
        return 1;
	}
}


void TForm4::jarvis_march(vector<Segment> &convex_hull, vector<Tacka> points){

	convex_hull.clear();
	Tacka start = points[0];
	for(int i = 1; i < points.size(); i++) {
		if(points[i].x < start.x) {
			start = points[i];
		}
    }


	Tacka current = start;
	vector<Tacka> collinearPoints;

	while(true) {

		Tacka next_target = points[0];
        for(int i = 1; i < points.size(); i++) {
			if(points[i] == current) {
				continue;
            }

			double value = orientation_of_points(current,next_target,points[i]);
			if(value == 1) {
				next_target = points[i];
				collinearPoints.clear();
			}else if(value == 0) {
				if(distance(current,next_target,points[i]) == -1) {
					collinearPoints.push_back(next_target);
					next_target = points[i];
				}else if(distance(current,next_target,points[i]) == 1){
					collinearPoints.push_back(points[i]);
				}

            }

		}

		for(int i = 0; i < collinearPoints.size(); i++) {
			if(i == 0){
				convex_hull.push_back(Segment(current,collinearPoints[i]));
			}else{
				convex_hull.push_back(Segment(collinearPoints[i-1],collinearPoints[i]));
			}
		}

		if(next_target == start) {
			convex_hull.push_back(Segment(current,next_target));
            break;
		}

		convex_hull.push_back(Segment(current,next_target));
		current = next_target;

	}

}



void TForm4::draw_label(Tacka A, int first, int second){
    TLabel *label = new TLabel(this);
	label->Parent = this;
	label->Height = 20;
	label->Width = 20;
	if(second == -1){
		label->Caption = first;
	}else{
		char a = first + '0';
		char b = second + '0';
		char niz[10] = {a,'-',b};
		label->Caption = niz;
    }

	label->Visible = true;
	label->Left = A.x-5;
	label->Top = A.y-5;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button5Click(TObject *Sender)
{
	Tacka first_station;
	int index;
	double distance = INT_MAX;
	for(int i = 0; i < stations.size(); i++){
		double temp_distance = get_distance(earth,stations[i].point);
		if(temp_distance < distance){
			distance = temp_distance;
			first_station = stations[i].point;
			index = stations[i].index;
		}
	}


	Segment earth_mars = Segment(earth,mars);
	vector<BCS> result_points;
	result_points.push_back(BCS(earth,index,0));
	for(int i = 0; i < voronoi_edges.size(); i++){
		if(intersect_segment(earth_mars,voronoi_edges[i].segment)){
			Tacka A = intersection_point(earth_mars,voronoi_edges[i].segment);
			result_points.push_back(BCS(A,voronoi_edges[i].first_neighbour,voronoi_edges[i].second_neighbour));
		}
	}


	Tacka last_station;
	int idx;
	double dist = INT_MAX;
	for(int i = 0; i < stations.size(); i++){
		double temp_distance = get_distance(mars,stations[i].point);
		if(temp_distance < dist){
			dist = temp_distance;
			last_station = stations[i].point;
			idx = stations[i].index;
		}
	}

	result_points.push_back(BCS(mars,idx,0));

	sort(result_points.begin(),result_points.end(),compare);

	if(result_points[0].point == earth){
		int start_index = result_points[0].first_neighbour;
		draw_label(earth,start_index,-1);
		for(int i = 1; i < result_points.size()-1; i++){
			int first = result_points[i].first_neighbour;
			int second = result_points[i].second_neighbour;
			int index_to_draw;
			Image1->Canvas->Brush->Color = clLime;
			Image1->Canvas->Ellipse(result_points[i].point.x-4,result_points[i].point.y-4,result_points[i].point.x+4,result_points[i].point.y+4);
			if(first == start_index && second != 0){
				index_to_draw = second;
				draw_label(result_points[i].point,start_index,second);
				start_index = second;
			}else if(second == start_index && first != 0){
				index_to_draw = first;
				draw_label(result_points[i].point,start_index,first);
				start_index = first;
			}
		}
		Image1->Canvas->Brush->Style = bsClear;
		Image1->Canvas->Ellipse(mars.x-4,mars.y-4,mars.x+4,mars.y+4);
		if(start_index == idx){
			draw_label(mars,idx,-1);
		}else{
			draw_label(mars,start_index,idx);
		}
	}else{
		int n = result_points.size();
		int start_index = result_points[n-1].first_neighbour;
		draw_label(earth,start_index,-1);
		for(int i = n-2; i > 0; i--){
			int first = result_points[i].first_neighbour;
			int second = result_points[i].second_neighbour;
			int index_to_draw;
			Image1->Canvas->Brush->Color = clLime;
			Image1->Canvas->Ellipse(result_points[i].point.x-4,result_points[i].point.y-4,result_points[i].point.x+4,result_points[i].point.y+4);
			if(first == start_index && second != 0){
				index_to_draw = second;
				draw_label(result_points[i].point,start_index,second);
				start_index = second;
			}else if(second == start_index && first != 0){
				index_to_draw = first;
				draw_label(result_points[i].point,start_index,first);
				start_index = first;
			}
		}
		Image1->Canvas->Brush->Style = bsClear;
		Image1->Canvas->Ellipse(mars.x-4,mars.y-4,mars.x+4,mars.y+4);
		if(start_index == idx){
			draw_label(mars,idx,-1);
		}else{
			draw_label(mars,start_index,idx);
		}

    }




}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

