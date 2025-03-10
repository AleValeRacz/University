#include "UndoRedo.h"

void ActionAdd::executeUndo() const
{
	this->repo.remove_tutorial(this->repo.find_position(this->addedTutorial.get_title()));

}

void ActionAdd::executeRedo() const
{
	this->repo.add_tutorial(this->addedTutorial);
}

void ActionRemove::executeUndo() const
{
	this->repo.add_tutorial(this->removedTutorial);
}

void ActionRemove::executeRedo() const
{
	this->repo.remove_tutorial(repo.find_position(this->removedTutorial.get_title()));
}

void ActionUpdate::executeUndo() const
{
	this->repo.update_tutorial(this->repo.find_position(this->newTutorial.get_title()), this->oldTutorial);

}

void ActionUpdate::executeRedo() const
{
	this->repo.update_tutorial(this->repo.find_position(this->oldTutorial.get_title()), this->newTutorial);
}

