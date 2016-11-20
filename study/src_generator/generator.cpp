#include "generator.h"


Generator::Generator(Configuration *configuration) : GeneratorAbstract::GeneratorAbstract(configuration)
{
}

vector<Task *> Generator::Generate()
{
    double min_offset = 0.0, max_offset = 100.0;
    double deviation = 0.5;
    double average_wcet = 100.0;
    double period;

    if (this->configuration->getUtilisation() > 0.0)
        period = average_wcet * this->configuration->getTaskNumber() / this->configuration->getUtilisation() * 100;
    else
    {
        period = 10.0;
        average_wcet = 0.0;
    }

    // generating offsets

    for (int i = 0; i < this->configuration->getTaskNumber(); i++)
        this->result.at(i)->setOffset(random(min_offset, max_offset));

    // generating utils (array of utilisation of every task)

    vector<double> utils;
    double utilisation_left = this->configuration->getUtilisation();
    double n = (double) this->configuration->getTaskNumber();

    for (int i = 0; i < this->configuration->getTaskNumber() - 1; i++)
    {
        double next = random(utilisation_left / n * (1.0 - deviation), utilisation_left / n * (1.0 + deviation));
        utilisation_left -= next;
        n--;
        utils.push_back(next);
    }

    if (this->configuration->getTaskNumber() > 0)
        utils.push_back(utilisation_left);

    // generating periods

    for (int i = 0; i < this->configuration->getTaskNumber(); i++)
        this->result.at(i)->setPeriod(period);

    // generating WCETs

    for (int i = 0; i < this->configuration->getTaskNumber(); i++)
        this->result.at(i)->setWcet(result.at(i)->getPeriod() * utils.at(i) / 100.0);

    // generating deadlines

    for (int i = 0; i < this->configuration->getTaskNumber(); i++)
        this->result.at(i)->setDeadline(random(this->result.at(i)->getWcet(), this->result.at(i)->getPeriod()));

    return result;
}
