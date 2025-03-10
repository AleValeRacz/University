#pragma once
#include "Tutorial.h"
#include "Repository.h"
class Action
{

public: 
	virtual void executeUndo() const = 0;
	virtual void executeRedo() const = 0;

};

class ActionAdd : public Action
{
private:
	Tutorial& addedTutorial;
	Repository& repo;
public:
	ActionAdd(Tutorial &t, Repository &r) : addedTutorial{ t }, repo{ r } {};
	void executeUndo() const override;
	void executeRedo() const override;

};


class ActionRemove : public Action
{
private:
	Tutorial& removedTutorial;
	Repository& repo;
public:
	ActionRemove(Tutorial &t, Repository &r) : removedTutorial{ t }, repo{ r } {};
	void executeUndo() const override;
	void executeRedo() const override;

};

class ActionUpdate : public Action
{
private:
	Tutorial& oldTutorial;
	Tutorial& newTutorial;
	Repository& repo;
public:
	ActionUpdate(Tutorial &ot, Tutorial &nt, Repository &r) : oldTutorial{ ot }, newTutorial{ nt }, repo { r } {};
	void executeUndo() const override;
	void executeRedo() const override;

};
