#include "generator.h"


Generator::Generator(Configuration *configuration) : GeneratorAbstract::GeneratorAbstract(configuration)
{
}


vector<Task *> Generator::Generate()
{
    double min_offset = 0.0, max_offset = 100.0;
    double deviation = 0.5;
    double min_period = 50.0, max_period = 100.0;

    // generating offsets

    for (int i = 0; i < this->configuration->getTask_number(); i++)
        this->result.at(i)->setOffset(random(min_offset, max_offset));

    // generating utils (array of utilisation of every task)

    vector<double> utils;
    double left = this->configuration->getUtilisation();
    double n = (double) this->configuration->getTask_number();

    for (int i = 0; i < this->configuration->getTask_number() - 1; i++)
    {
        double next = random(left / n * (1.0 - deviation), left / n * (1.0 + deviation));
        left -= next;
        n--;
        utils.push_back(next);
    }
    utils.push_back(left);

    // generating periods

    for (int i = 0; i < this->configuration->getTask_number(); i++)
        this->result.at(i)->setPeriod(random(min_period, max_period));

    // generating WCETs

    for (int i = 0; i < this->configuration->getTask_number(); i++)
        this->result.at(i)->setWcet(result.at(i)->getPeriod() * utils.at(i) / 100.0);

    // generating deadlines

    for (int i = 0; i < this->configuration->getTask_number(); i++)
        this->result.at(i)->setDeadline(random(this->result.at(i)->getWcet(), this->result.at(i)->getPeriod()));

    return result;
}
