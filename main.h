//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "pomocna.h"
#include <algorithm>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *Button3;
	TStaticText *StaticText1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TButton *Button5;
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
	int ses_index;
	Tacka center;
	Tacka earth;
	Tacka mars;
	double earth_radius;
	double mars_radius;
    double jupiter_radius;
	double orientation_of_points(Tacka A, Tacka B, Tacka C);
	vector<SES> stations;
	vector<Tacka> points;
	vector<VE> voronoi_edges;
	bool intersect_segment(Segment A, Segment B);
	Tacka intersection_point(Segment A, Segment B);
	bool point_on_segment(Tacka A, Tacka B, Tacka C);
	Segment perpendicular_bisector(Segment S);
	Segment increase_segment_length(Segment S);
	void intersection_convex_hull_and_segment(vector<Segment> &convex_hull, Segment pb);
	int index;
	void jarvis_march(vector<Segment> &convex_hull, vector<Tacka> points);
	int distance(Tacka A, Tacka B, Tacka C);
	double get_distance(Tacka A, Tacka B);
	bool compare(BCS A, BCS B);
	void draw_label(Tacka A, int first, int second);
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
