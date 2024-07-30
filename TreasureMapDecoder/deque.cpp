/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque() : n1(0), n2(-1) {

}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    n2++;
    if (n2 < static_cast<int>(data.size())) {
        data[n2] = newItem;
    } else {
        data.push_back(newItem);
    }
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T removedItem = data[n1];
    n1++;
    if (n2 - n1 + 1 <= n1) {
        std::vector<T> newData;
        for (int i = n1; i <= n2; i++) {
            newData.push_back(data[i]);
        }
        data = newData;
        n2 -= n1;
        n1 = 0;
    }
    return removedItem;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    // Assuming the deque is not empty, retrieve the rightmost item
    T removedItem = data[n2];
    
    // Decrement n2 as we're removing the rightmost item
    n2--;

    // Check if data can fit into indices 0 to n2+1
    if (n2 - n1 + 1 <= n1) {
        std::vector<T> newData(n2 - n1 + 1);

        // Copy data from n1 to n2 into the beginning of newData
        for (int i = n1, j = 0; i <= n2; i++, j++) {
            newData[j] = data[i];
        }
        
        // Update the data vector to the new resized vector
        data = newData;

        // Adjust n2 index based on the items moved
        n2 -= n1;

        // Reset n1 to 0 as we've resized the deque to start from the beginning
        n1 = 0;
    }
   return removedItem;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return n1 > n2;
}
