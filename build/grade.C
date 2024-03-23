#include <iostream>
#include <fstream>

float grade(){

  string path = "N500_x0.45.root";

  TFile *f = new TFile(path.c_str());

  //TH1F * h1 = (TH1F*)f->Get(“delta_E_good”);
  TTree *tree = (TTree*)f->Get("Hits;1");
  TLeaf *leaf = (TLeaf*)tree->GetLeaf("delta_E_good");

  int entries = tree->GetEntries();
  
  double Eg = 0;
  double Eb = 0;
  for(int i = 0; i<entries; i++)
    {
      tree->GetEntry(i);
      Eg = Eg + tree->GetLeaf("delta_E_good")->GetValue(0);
      Eb = Eb + tree->GetLeaf("delta_E_bad")->GetValue(0);
    }
  cout<<Eb<<" "<<Eg<<endl;
  double grade = Eg/(Eg + Eb) * 100;
  cout<<"Your grade is: "<<grade<<endl;
  return grade;
}
