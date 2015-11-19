//------------------------------------------------------------------------------------------------
// Author: Sixing Lu
// Date Created: 1 January 2014
//
// Description: The defination of functions
//------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctype.h>
#include "access.h"

using namespace std;

// constructor of class Object
Object::Object(string name,bool own,bool read,bool write)
{
	this->obj_name =name;
	this->right_own =own;
	this->right_read =read;
	this->right_write =write;

	this->obj_next =NULL;
	this->obj_prev =NULL;

}

// constructor of class Subject
Subject::Subject(string name)
{
	this->subj_name =name;
	this->sub_next =NULL;
	this->sub_prev =NULL;
	this->obj_head =NULL;
	this->obj_tail =NULL;
}

AccessMat::AccessMat()
{
   this->subj_head =NULL;
   this->subj_tail =NULL;
}

// create a subject into access matrix
bool AccessMat::Creat_Subj(string subName)
{
	Subject* newsubj =new Subject(subName);

	if(this->find_subj(subName)!=NULL){
		cout<<"the Subject already exists!"<<endl;
		return false;
	}

	if(this->Get_subjhead()==NULL){
		this->move_shead(newsubj);
		this->move_stail(newsubj);
	}
	else{
        this->Get_subjtail()->change_snext(newsubj);
		newsubj->change_sprev(this->Get_subjtail());
        this->move_stail(newsubj);
	}

	return true;
}

// modify right of one subject to one object
bool AccessMat::Modi_allright(string subName,string objName,bool own,bool read,bool write)
{
	Subject* target_sub =this->find_subj(subName);
	if(target_sub==NULL){
		cout<<"there is no "<<subName<<endl;
		return false;
	}
    Object* target_obj =target_sub->find_obj(objName);
	if(target_obj==NULL){   // if the object is not in the list
		Object* newobj;
		if(own==1&&read==1&&write==1){
		    newobj =new Object(objName,true,true,true);
		}
		else if(own!=1){
			newobj =new Object(objName,own,read,write);
		}
		else{ //own==1 but others not
			cout<<"warming: when right own is true, other rights would automatic be true!"<<endl;
			newobj =new Object(objName,true,true,true);
		}

		if(target_sub->Get_objhead()==NULL){
			target_sub->move_ohead(newobj);
			target_sub->move_otail(newobj);
		}
		else{
            target_sub->Get_objtail()->change_onext(newobj);
			newobj->change_oprev(target_sub->Get_objtail());
		    target_sub->move_otail(newobj); 
		}
	}
	else{
		if(own==1&&(read!=1||write!=1)){
            cout<<"warming: when right own is true, other rights would automatic be true!"<<endl;
			target_obj->Input_own(true);
			target_obj->Input_read(true);
			target_obj->Input_write(true);
		}
		else{
			target_obj->Input_own(own);
			target_obj->Input_read(read);
			target_obj->Input_write(write);
		}
	}

	return true;
}

// add single right of one object to one subject 
bool AccessMat::Add_indivright(string subName,string objName, string type)
{
    Subject* target_sub =this->find_subj(subName);
	if(target_sub==NULL){
		cout<<"there is no "<<subName<<endl;
		return false;
	}
    Object* target_obj =target_sub->find_obj(objName);
	if(target_obj==NULL){   // if the object is not in the list
        Object* newobj;
		if(type=="o"){
			cout<<"warning: when add own right, the read/write will automatically activated!"<<endl;
			newobj =new Object(objName,true,true,true); // if the object is owned by subject, obviously it can read/write it
		}
		else if(type=="r"){
			newobj =new Object(objName,false,true,false);
		}
		else if(type=="w"){
			newobj =new Object(objName,false,false,true);
		}
		else{
			cout<<"please input right type: "<<endl;
			cout<<"-o add own right"<<endl;
			cout<<"-r add read right"<<endl;
			cout<<"-w add write right"<<endl;
			return false;
		}
        // add the object into list
		if(target_sub->Get_objhead()==NULL){
			target_sub->move_ohead(newobj);
			target_sub->move_otail(newobj);
		}
		else{
            target_sub->Get_objtail()->change_onext(newobj);
			newobj->change_oprev(target_sub->Get_objtail());
		    target_sub->move_otail(newobj); 
		}
	}
	else{ // the object already exist
		if(type=="o"){
			target_obj->Input_own(true);
		}
		else if(type=="r"){
			target_obj->Input_read(true);
		}
		else if(type=="w"){
			target_obj->Input_write(true);
		}
		else{
			cout<<"please input right type: "<<endl;
			cout<<"-o add own right"<<endl;
			cout<<"-r add read right"<<endl;
			cout<<"-w add write right"<<endl;
			return false;
		}
	    
	}
    return true;
}

// delete single right of one object from one subject
bool AccessMat::Dele_indivright(string subName,string objName, string type)
{
	Subject* target_sub =this->find_subj(subName);
	if(target_sub==NULL){
		cout<<"there is no "<<subName<<endl;
		return false;
	}
    Object* target_obj =target_sub->find_obj(objName);
	if(target_obj==NULL){   // if the object is not in the list
		cout<<subName<<" does not have any right to "<<objName<<endl;
		return false;
	}
	else{ // the object already exist
		if(type=="o"){
			target_obj->Input_own(false);
		}
		else if(type=="r"){
			if(target_obj->Get_own()==true){
				cout<<"could not delete r for "<<target_obj->Get_name()<<" because "<<target_sub->Get_name()<<" own this file"<<endl;
				return 0;
			}
			else{
			    target_obj->Input_read(false);
			}
		}
		else if(type=="w"){
			if(target_obj->Get_own()==true){
				cout<<"could not delete w for "<<target_obj->Get_name()<<" because "<<target_sub->Get_name()<<" own this file"<<endl;
				return 0;
			}
			else{
			   target_obj->Input_write(false);
			}
		}
		else{
			cout<<"please input right type: "<<endl;
			cout<<"-o add own right"<<endl;
			cout<<"-r add read right"<<endl;
			cout<<"-w add write right"<<endl;
			return false;
		}
	    
	}

    return true;
}

// delete subject from access matrix
bool AccessMat::Dele_subj(string subName)
{
	Subject* target =this->find_subj(subName);

	if(target==NULL){
		cout<<"there is no "<<subName<<endl;
		return false;
	}

	Subject* prev =target->Get_sprev();
    Subject* next =target->Get_snext();
	if(target->Get_name()==this->Get_subjhead()->Get_name()){
		this->move_shead(next);
		if(next!=NULL){
		   next->change_sprev(NULL);
		}
		delete target;
	}
	else if(target->Get_name()==this->Get_subjtail()->Get_name()){
		this->move_stail(prev);
		if(prev!=NULL){
		   prev->change_snext(NULL);
		}
		delete target;
	}
	else{
		prev->change_snext(next);
		next->change_sprev(prev);
		delete target;
	}
	return true;

}

// delete object from access matrix
bool AccessMat::Dele_obj(string objName)
{   
	bool flag =0;
    Subject* traverse_sub =this->Get_subjhead();
	while(traverse_sub!=NULL){
		if(traverse_sub->find_obj(objName)){
			traverse_sub->Dele_singleobj(objName);
			flag =1;
		}
		traverse_sub =traverse_sub->Get_snext();
	}

	if(flag==0){
		cout<<"there is no "<<objName<<" in the Matrix!"<<endl;
		return false;
	}

    return true;
}

// help function to delete object
bool Subject::Dele_singleobj(string objName)
{
    Object* target =this->find_obj(objName);

	if(target==NULL){
		return false;
	}

	Object* prev =target->Get_oprev();
    Object* next =target->Get_onext();
	if(target->Get_name()==this->Get_objhead()->Get_name()){
		this->move_ohead(next);
		if(next!=NULL){
		   next->change_oprev(NULL);
		}
		delete target;
	}
	else if(target->Get_name()==this->Get_objtail()->Get_name()){
		this->move_otail(prev);
		if(prev!=NULL){
		   prev->change_onext(NULL);
		}
		delete target;
	}
	else{
		prev->change_onext(next);
		next->change_oprev(prev);
		delete target;
	}
	return true;
}

// help funtion to find a subject
Subject* AccessMat::find_subj(string subName)
{
	if(this->subj_head==NULL){
		return NULL;
	}

    Subject* temp =this->subj_head;

	while(temp!=NULL){
		if(temp->Get_name()==subName){
			return temp;
		}
		temp =temp->Get_snext();
	}

	return NULL;

}

// help function to find a object
Object* Subject::find_obj(string Name)
{
	if(this->obj_head==NULL){
		return NULL;
	}

	Object* temp =this->obj_head;

	while(temp!=NULL){
		if(temp->Get_name()==Name){
			return temp;
		}
		temp =temp->Get_onext();
	}
	return NULL;

}

// test function to print out access matrix
void AccessMat::Print_Matrix()
{
	printf("\nThe Access Matrix is:\n");
    Subject* traverse_sub =this->Get_subjhead();
	while(traverse_sub!=NULL){
		cout<<traverse_sub->Get_name()<<" :"<<endl;
		Object* traverse_obj =traverse_sub->Get_objhead();
		while(traverse_obj!=NULL){
			cout<<traverse_obj->Get_name()<<"-- o "<<traverse_obj->Get_own()<<"  r "<<traverse_obj->Get_read()<<"  w "<<traverse_obj->Get_write()<<endl;
			traverse_obj =traverse_obj->Get_onext();
		}
		traverse_sub =traverse_sub->Get_snext();
	}

}