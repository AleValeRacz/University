#include "repository.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamic_array.h"
#include <assert.h>

#pragma warning(disable: 4996)

Repository* create_repository()
{
	Repository* r = (Repository*)malloc(sizeof(Repository));
	r->medicines = createDynamicArray(10, (destroyFunction)& destroy_medicine);
	return r;
}
void destroy_repository(Repository* r)
{
	if (r == NULL)
		return;
	destroyDynamicArray(r->medicines);
	free(r);
}
DynamicArray* get_dynamic_array(Repository* r)
{
	return r->medicines;
}
int get_repo_length(Repository* r)
{
	return getSize(get_dynamic_array(r));
} 

int find_position(Repository* r, Medicine* m)
{
	for (int i = 0; i < get_repo_length(r); i++)
	{
		Medicine* medicine = get_medicine_on_pos(r, i);
		 if (strcmp(get_name(m), get_name(medicine)) == 0 && get_concentration(medicine) == get_concentration(m))
			return i;
	}
	return -1;

}

int add_medicine(Repository* r, Medicine* m)
{
	if (r == NULL || m == NULL)
		return 0;
	addElemToArray(get_dynamic_array(r), m);
	return 1;
}
void delete_medicine(Repository* r,int pos)
{
	if (r == NULL || pos < 0 || pos >= get_repo_length(r))
		return;
	deleteElemFromArray(get_dynamic_array(r), pos);


}
Medicine* find(Repository* r, char* name, double concentration)
{
	for (int i = 0; i < get_repo_length(r); i++)
	{
		Medicine* medicine = get_medicine_on_pos(r, i);
		if (strcmp(get_name(medicine), name) == 0 && get_concentration(medicine) == concentration)
			return medicine;
	}
	return NULL;
}

Medicine* get_medicine_on_pos(Repository* r, int pos)
{
	if (r == NULL)
		return NULL;
	Medicine* m = (Medicine*)get(r->medicines, pos);
	return m;
}
void update_medicine(Repository* r,int pos, Medicine* m)
{


	update_element_on_position(r->medicines, pos, m);

}
void initial_input(Repository* r)
{
	char name[50];
	strcpy(name, "Nurofen");
	Medicine* m = create_medicine(name, 200, 17, 8);
	add_medicine(r, m);
	
	strcpy(name, "Algocalmin");
	m = create_medicine(name, 200, 17, 8);
	add_medicine(r, m);


	strcpy(name, "Concerta");
	 m = create_medicine(name, 36, 100, 88);
	add_medicine(r, m);


	strcpy(name, "Paracetamol");
	 m = create_medicine(name, 86, 45, 27.5);
	add_medicine(r, m);

	
	strcpy(name, "Teraflu");
	 m = create_medicine(name, 70, 121, 12);
	add_medicine(r, m);


	strcpy(name, "Coldrex");
	m = create_medicine(name, 99, 5, 34);
	add_medicine(r, m);


	strcpy(name, "Strepsils");
	 m = create_medicine(name, 880, 10, 120);
	add_medicine(r, m);


	strcpy(name, "Faringosept");
	m = create_medicine(name, 30, 78, 16);
	add_medicine(r, m);


	strcpy(name, "Propolis");
	 m = create_medicine(name, 78,43,8);
	add_medicine(r, m);


	strcpy(name, "Dropsils");
	m = create_medicine(name, 23, 451, 79);
	add_medicine(r, m);
	

}

void test_repo()
{
	Repository* r = create_repository();
	char name[50];
	strcpy(name, "Algocalmin");

	//test create empty repo
	assert(get_repo_length(r) == 0);

	//test create medicine and add medicine
	Medicine* m1 = create_medicine(name, 13, 4, 5);
	add_medicine(r, m1);
	assert(get_repo_length(r) == 1);

	//test find
	assert(find(r, name, 13) == m1);
	strcpy(name, "Parasinus");
	Medicine* m2 = create_medicine(name, 20, 1, 4);
	strcpy(name, "Apa");
	add_medicine(r, m2);
	Medicine* m3 = create_medicine(name, 20, 1, 4);
	add_medicine(r, m3);
	strcpy(name, "Aba");
	Medicine* m4 = create_medicine(name, 20, 1, 4);
	add_medicine(r, m4);

	//test find position
	assert(find_position(r, m3) ==2);
	//test delete

	delete_medicine(r, find_position(r, m2));
	assert(get_repo_length(r) == 3);
	//test update

	Medicine* m5 = create_medicine(name, 2, 4, 5);
	update_medicine(r, 1, m5);
	assert(find_position(r, m5) == 1);
	
}


