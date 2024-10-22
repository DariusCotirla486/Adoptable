#pragma once
#include "Repository.h"


class Operation {
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};


class AddOperation : public Operation {
private:
	Repository& repo;
	Dog added_element;

public:
	AddOperation(Repository& repo, Dog added_element);
	void executeUndo() override;
	void executeRedo() override;
};


class RemoveOperation : public Operation {
private:
	Repository& repo;
	Dog removed_element;

public:
	RemoveOperation(Repository& repo, Dog removed_element);
	void executeUndo() override;
	void executeRedo() override;
};