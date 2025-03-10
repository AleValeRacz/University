#include "Tests.h"
#include "tutorial.h"
#include "repository.h"
#include "service.h"
#include "dynamic_vector.h"
#include <cassert>
void TestRepository()
{
	cout << "Testing repo.."<<endl;
	//Test creating repo
	Repository repo;
	assert(repo.get_tutorials().get_size() == 10);

	//Test adding a tutorial to repo
	Tutorial tutorial("New one", "STL Guru", make_pair(50, 45), 280, "https://www.youtube.com/wa12");
	repo.add_tutorial(tutorial);
	assert(repo.get_tutorials().get_size() == 11);
	assert(repo.find_position("New one") == 10);

	//Test removing tutorial from repo
	repo.remove_tutorial(10);
	assert(repo.get_tutorials().get_size() == 10);
	assert(repo.find_position("New one") == -1);

	//Test find function
	assert(repo.find_position("Become a C++ expert!") == 3);
	assert(repo.find_position("won't be here") == -1);

	//Test updateing tutorial
	Tutorial updatedTutorial("New Title", "New Presenter", { 15, 45 }, 200, "https://example.com/new");
	repo.update_tutorial(1, updatedTutorial);
	assert(repo.get_tutorials()[1].get_presenter() == "New Presenter");

	//Test setters
	Tutorial tut("am", "df", { 12,4 }, 677, "https://www.youtube.com/wa12");
	repo.add_tutorial(tut);
	tut.set_likes(5);
	assert(tut.get_likes() == 5);
	tut.set_link("dfgh");
	tut.set_minutes(21);
	tut.set_seconds(8);
	tut.set_presenter("agh");
	tut.set_title("am");
	assert(tut.get_link() == "dfgh");
	assert(tut.get_minutes() == 21);
	assert(tut.get_seconds() == 8);

	//Get tutorial by title
	assert(repo.get_tutorial_by_title("am").get_title() == tut.get_title());
	try
	{
		repo.get_tutorial_by_title("aleee");
	}
	catch (exception& e)
	{ }
}

void TestService()
{
	cout << "Testing service..." << endl;
	Service service;

	// Test adding a tutorial in service
	Tutorial tutorial("Title", "Presenter", { 10, 30 }, 100, "https://example.com");
	service.add_tutorial(tutorial);
	assert(service.get_tutorials().get_size() == 11);

	try
	{
		service.add_tutorial(tutorial);
	}
	catch (exception& e)
	{}
		

	//Test removing a tutorial from service
	service.remove_tutorial("Title");
	assert(service.get_tutorials().get_size() == 10);

	//Test updating tutorial
	service.add_tutorial(tutorial);
	service.update_tutorial("Title", "New Presenter",15,14, 200, "https://example.com/new");
	assert(service.get_tutorials()[10].get_presenter() == "New Presenter");

	//Test validate tutorial
	Tutorial t("Title", "Presenter", { 10, 30 }, 100, "https://example.com");

	assert(service.validate_tutorial(t) == true);
	Tutorial t1("Title", "Presenter", { -12, 87 }, 100, "https://example.com");
	assert(service.validate_tutorial(t1) == false);
	Tutorial t2("bb", "fff", { 12, 5 }, -100, "https://example.com");
	assert(service.validate_tutorial(t2) == false);
	Tutorial t3("b", "", { 12, 5 }, 100, "https://example.com");
	assert(service.validate_tutorial(t3) == false);
	//Test filter by presenter
	DynamicVector<Tutorial> ts;
	ts = service.filter_by_presenter("C++Wizard");
	assert(ts.get_size() == 2);

	//Test add to watchlist
	service.add_to_watchlist(tutorial);
	assert(service.get_watchlist().get_size() == 1);

	//Test remove from watchlist
	service.remove_from_watchlist(tutorial.get_title());
	assert(service.get_watchlist().get_size() == 0);

	//Test like a tutorial
	t = service.get_tutorials()[0];
	service.like_tutorial(t.get_title());
	assert(service.get_tutorials()[0].get_likes() == t.get_likes() + 1);
	
}
void test_dynamic_vector() 
{
	cout << "Testing dynamic vector.." << endl;

	DynamicVector<int> vector = DynamicVector<int>();

	// Test adding elements
	vector.add(10);
	vector.add(20);
	assert(vector.get_size() == 2);


	//Test operator []
	assert(vector.operator[](1) == 20);

	// Test removing elements
	vector.remove(0);
	assert(vector.get_size() == 1);
	assert(vector.operator[](0) == 20);
	try
	{
		vector.remove(-1);
	}
	catch (exception& e)
	{}

	

	//Test operator []
	assert(vector.operator[](1) == 20);

	// Test updating elements
	vector.add(30);
	vector.update(1,12);
	assert(vector.operator[](1) == 12);
	try
	{
		vector.update(-1,8);
	}
	catch (exception& e)
	{}
	
}