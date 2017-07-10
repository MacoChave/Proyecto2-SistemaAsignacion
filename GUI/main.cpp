#include "gui.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	return new GUI(env);
}

int main(int argc, char *argv[])
{
	return Wt::WRun(argc, argv, &createApplication);
}
