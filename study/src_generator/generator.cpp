#include "generator.h"


Generator::Generator(Configuration *configuration) : GeneratorAbstract::GeneratorAbstract(configuration)
{
}

vector<Task *> Generator::Generate()
{
    double min_offset = 0.0, max_offset = 100.0;
    double deviation = 0.5;
    double period;

    if (configuration->getUtilisation() > 0.0)
        period = configuration->getAverageWcet() * configuration->getTaskNumber() / configuration->getUtilisation() * 100;
    else
        period = 10.0;

    // generating offsets

    for (int i = 0; i < configuration->getTaskNumber(); i++)
        result.at(i)->setOffset(random(min_offset, max_offset));

    // generating utils (array of utilisation of every task)

    vector<double> utils;
    double utilisation_left = configuration->getUtilisation();
    double n = (double) configuration->getTaskNumber();

    for (int i = 0; i < configuration->getTaskNumber() - 1; i++)
    {
        // utilisation generation range essential limits correction

        double min_utilisation = utilisation_left / n * (1.0 - deviation);

        if (min_utilisation < 0.0)
            min_utilisation = 0.0;
        if (min_utilisation > 100.0)
            min_utilisation = 100.0;

        // extra check (we can not leave more than 100 x [processors_left - 1] for the rest processors)

        double min_utilisation_2 = utilisation_left - 100.0 * (configuration->getTaskNumber() - i - 1);
        if ((min_utilisation_2 > 0.0) && (min_utilisation < min_utilisation_2))
            min_utilisation = min_utilisation_2;

        double max_utilisation = utilisation_left / n * (1.0 + deviation);

        if (max_utilisation < 0.0)
            max_utilisation = 0.0;
        if (max_utilisation > 100.0)
            max_utilisation = 100.0;

        double next = random(min_utilisation, max_utilisation);    // utilisation generation
        utilisation_left -= next;
        n--;
        utils.push_back(next);
    }

    if (configuration->getTaskNumber() > 0)
        utils.push_back(utilisation_left);

    // generating periods

    for (int i = 0; i < configuration->getTaskNumber(); i++)
        result.at(i)->setPeriod(period);

    // generating WCETs

    for (int i = 0; i < configuration->getTaskNumber(); i++)
        result.at(i)->setWcet(result.at(i)->getPeriod() * utils.at(i) / 100.0);

    // generating deadlines

    for (int i = 0; i < configuration->getTaskNumber(); i++)
        result.at(i)->setDeadline(random(result.at(i)->getWcet(), result.at(i)->getPeriod()));

    return result;
}
