#include "Validator.h"
#include "Exception.h"

bool validString(const string& str)
{
	if (str.empty())
		return false;
	return true;
}

void Validator::validate_tutorial(Tutorial& t)
{
	string errors;
	if (!validString(t.get_title()))
		errors.append("Invalid title!\n");
	if (!validString(t.get_presenter()))
		errors.append("Invalid presenter!\n");
	if (!validString(t.get_link()))
		errors.append("Invalid link!\n");
	if (t.get_minutes() < 0)
		errors.append("Invalid minutes!\n");
	if (t.get_seconds() < 0 || t.get_seconds() > 59)
		errors.append("Invalid seconds\n");
	if (t.get_likes() < 0)
		errors.append("Invalid likes\n");
	if (!errors.empty())
		throw Exception(errors);

}
