//------------------------------------------------------------------------------------------------
//
// Author: Sixing Lu
// Date Created: 1 January 2014
//
// Description: The entrance of Access Matrix
//
//------------------------------------------------------------------------------------------------

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include "access.h"

//------------------------------------------------------------------------------------------------

using namespace std;
void correct_command();
bool char2bool(string right);

//------------------------------------------------------------------------------------------------

int
main()
{	
	AccessMat accessmatrix;
	while(1){  //contiue input command line
	   cout<<"Please input command (input help if you do not know the command)"<<endl;
	   string argvs;
      // char *argv[10];
       
	   getline(cin,argvs);

	   istringstream getword(argvs); 
	   string token;
	   vector<string> vec(0);
	   while(!getword.eof()){
			if( (getword >>token).fail())
			   break;
			vec.push_back(token);
	   }
	   int argc =vec.size();

	   if ( !(argc == 1 || argc==3 || argc==4 || argc==7)) {
		   cout << "the command line is incorrect!" << endl;
		   correct_command();
		   //return -1;
	   }

	   if(argc==1){  // help
		   if( vec[0]!="help"){
			  cout << "the command line is incorrect!" << endl;
		   }
		   correct_command();
	   }
 
	   if(argc==3){
		   if(vec[0]=="create" && vec[1]=="subject"){  // create a subject
			   if(accessmatrix.Creat_Subj(vec[2])){
				   cout<<"subject creation successful!"<<endl;
			   }
			   else{
                   cout<<"subject creation fail!"<<endl;
			   }
		   }
		   else if(vec[0]=="delete" && vec[1]=="subject"){ // delete a subject
			   if(accessmatrix.Dele_subj(vec[2])){
				   cout<<"subject deletion successful!"<<endl;
			   }
			   else{
				   cout<<"subject deletion fail!"<<endl; 
			   }
		   }
		   else if(vec[0]=="delete" && vec[1]=="object"){ // delete a object
			   if(accessmatrix.Dele_obj(vec[2])){
                   cout<<"object deletion successful!"<<endl;
			   }
			   else{
				   cout<<"object deletion fail!"<<endl; 
			   }
		   }
		   else{
			   cout << "the command line is incorrect!" << endl;
			   correct_command();
			   //return -1;
		   }
	   }

	   if(argc==4){
		   if(vec[0]=="add"){
			   if(accessmatrix.Add_indivright(vec[2],vec[3],vec[1])){
				   cout<<"add right "<<vec[1]<<" successful!"<<endl;
			   }
			   else{
				   cout<<"add right "<<vec[1]<<" fail!"<<endl;
			   }
		   }
		   else if(vec[0]=="delete"){
			   if(accessmatrix.Dele_indivright(vec[2],vec[3],vec[1])){
				   cout<<"deletion right "<<vec[1]<<" successful!"<<endl;
			   }
			   else{
				   cout<<"deletion right "<<vec[1]<<" fail!"<<endl;
			   }
		   }
		   else{
			   cout << "the command line is incorrect!" << endl;
			   correct_command();
		   }
	   }

	   if(argc==7){
		   if((vec[4]!="1"&&vec[4]!="0") || (vec[5]!="1"&&vec[5]!="0") || (vec[6]!="1"&&vec[6]!="0")){
			   cout << "the command line is incorrect!" << endl;
			   correct_command();
		   }
		   else if(vec[0]=="modify" && vec[1]=="right"){
			   if(accessmatrix.Modi_allright(vec[2],vec[3],char2bool(vec[4]),char2bool(vec[5]),char2bool(vec[6]))){
				   cout<<"rights modification successful!"<<endl;
			   }
			   else{
				   cout<<"rights modification fail!"<<endl;
			   }
		   }
		   else if(vec[0]=="create" && vec[1]=="object"){
			   if(accessmatrix.Modi_allright(vec[2],vec[3],char2bool(vec[4]),char2bool(vec[5]),char2bool(vec[6]))){
				   cout<<"object creation successful!"<<endl;
			   }
			   else{
				   cout<<"object creation fail!"<<endl;
			   }
		   }
		   else{
			   cout << "the command line is incorrect!" << endl;
			   correct_command();
		   }
	   }

       accessmatrix.Print_Matrix();
	   cout<<endl;

	}
    return 0;
}

void correct_command()
{
	  cout<<"-create subject [Subject_Name]:  create a new subject into the access matrix"<<endl;   //argc==3
	  cout<<"-create object [Subject_Name] [Object_Name] [right_own] [right_read] [right_write]:   create object for subject"<<endl; //argc==7
	  cout<<"-modify right [Subject_Name] [Object_Name] [right_own] [right_read] [right_write]:  change rights between a subject and a object"<<endl;  //argc==7
	  cout<<"-add o [Subject_Name] [Object_Name]:  add subject right own to object"<<endl;  //argc==4
	  cout<<"-add r [Subject_Name] [Object_Name]:  add subject right read to object"<<endl;  //argc==4
	  cout<<"-add w [Subject_Name] [Object_Name]:  add subject right write to object"<<endl;  //argc==4
	  cout<<"-delete subject [Subject_Name]:  delete a subject from access matrix"<<endl; //argc==3
	  cout<<"-delete object [Object_Name]:  delete a object from access matrix"<<endl; //argc==3
	  cout<<"-delete o [Subject_Name] [Object_Name]:  delete subject right own from object"<<endl; //argc==4
	  cout<<"-delete r [Subject_Name] [Object_Name]:  delete subject right read from object"<<endl; //argc==4
	  cout<<"-delete w [Subject_Name] [Object_Name]:  delete subject right write from object"<<endl; //argc==4
	  cout<<"-help:  show all command line needed"<<endl; //argc==1
	  //cout<<"please input again"<<endl;

}

bool char2bool(string right)
{
	if(right=="0")
		return false;
	else if(right=="1")
		return true;
	else{
		cout<<"input right should be 0/1!"<<endl;
		return false;  
	}

}
//------------------------------------------------------------------------------------------------

