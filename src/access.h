//------------------------------------------------------------------------------------------------
// Author: Sixing Lu
// Date Created: 1 January 2014
//
// Description: The declarasion of class Object, Subject
//------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
#ifndef ACCESS_H
#define ACCESS_H
using namespace std;

class Object{
private:
	string obj_name;
	bool right_own;
	bool right_read;
	bool right_write;

	Object* obj_prev;
	Object* obj_next;

public:
	Object(string name,bool own=false,bool read=false,bool write=false);
	string Get_name(){return obj_name;}

	bool Get_own(){return right_own;}
	bool Get_read(){return right_read;}
	bool Get_write(){return right_write;}   
	void Input_own(bool own){right_own =own;}
    void Input_read(bool read){right_read =read;}
	void Input_write(bool write){right_write =write;}

	Object* Get_oprev(){return obj_prev;}
	Object* Get_onext(){return obj_next;}
	void change_oprev(Object* target){obj_prev =target;}
	void change_onext(Object* target){obj_next =target;}

};

class Subject{
private:
	string subj_name;
	Object* obj_head;
	Object* obj_tail;
    Subject* sub_prev;
	Subject* sub_next;

public:
	Subject(string name);

	string Get_name(){return subj_name;}
	Object* Get_objhead(){return obj_head;}
	Object* Get_objtail(){return obj_tail;}
	void move_ohead(Object* objhead){obj_head =objhead;}
	void move_otail(Object* objtail){obj_tail =objtail;}

	Subject* Get_sprev(){return sub_prev;}
	Subject* Get_snext(){return sub_next;}
	void change_sprev(Subject* target){sub_prev =target;}
	void change_snext(Subject* target){sub_next =target;}

	Object* find_obj(string Name);
	bool Dele_singleobj(string objName);
};

class AccessMat{
private:
	Subject* subj_head;
	Subject* subj_tail;
public:
	AccessMat();
	Subject* Get_subjhead(){return subj_head;}
	Subject* Get_subjtail(){return subj_tail;}
	void move_shead(Subject* subhead){subj_head =subhead;}
	void move_stail(Subject* subtail){subj_tail =subtail;}

	// functions use to modify Access Matrix
	bool Creat_Subj(string subName);
	bool Dele_subj(string subName);
	bool Dele_obj(string objName);
	bool Modi_allright(string subName,string objName,bool own,bool read,bool write);
	bool Add_indivright(string subName,string objName, string type);
	bool Dele_indivright(string subName,string objName, string type);

	// assisstant functions
	Subject* find_subj(string subName);
	void Print_Matrix();
};

#endif