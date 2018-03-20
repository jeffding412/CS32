…
inline
bool compareSensorPtr(const Sensor* lhs, const Sensor* rhs)
{
    return compareSensor(*lhs, *rhs);
}
…
void insertion_sort(vector<Sensor>& s, bool comp(const Sensor&, const Sensor&))
{
    for (size_t k = 1; k < s.size(); k++)
    {
        Sensor currentSensor(s[k]);
        size_t m = k;
        for ( ; m > 0  &&  comp(currentSensor, s[m-1]); m--)
            s[m] = s[m-1];
        s[m] = currentSensor;
    }
}
…
      // Create a auxiliary copy of sensors, to faciliate the later reordering.
      // We create it in a local scope, so that we also account for the
      // destruction time.
    {
     vector<Sensor> auxSensors(sensors);

      // Create a vector of Sensor pointers, and set each pointer
      // to point to the corresponding Sensor in auxSensors.
     vector<Sensor*> sensorPtrs;
     for (size_t k = 0; k < auxSensors.size(); k++)
         sensorPtrs.push_back(&auxSensors[k]);
    
      // Sort the vector of pointers using the STL sort algorithm
      // with compareSensorPtr as the ordering relationship.
     sort(sensorPtrs.begin(), sensorPtrs.end(), compareSensorPtr);

      // Using the now-sorted vector of pointers, replace each Sensor
      // in sensors with the Sensors from auxSensors in the correct order.
     for (size_t k = 0; k < sensorPtrs.size(); k++)
         sensors[k] = *sensorPtrs[k];

    } // auxSensors will be destroyed here
…
