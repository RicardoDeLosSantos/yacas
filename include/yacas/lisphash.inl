/** LAssoc is a helper class for LispAssociatedHash
 */
template<class T>
class LAssoc : public YacasBase
{
public:
  inline LAssoc(LispString * aString,const T& aData);
  inline ~LAssoc();
  LispStringSmartPtr iString;
  T iData;
private: //Functions no one is allowed to use
  inline LAssoc(const LAssoc& aOther);
  inline LAssoc& operator=(const LAssoc& aOther);
};
template<class T>
inline LAssoc<T>::LAssoc(LispString * aString,const T& aData)
: iString(),iData(aData)
{
  assert(aString);
  iString = aString;
}

template<class T>
inline LAssoc<T>::~LAssoc()
{
   iString = nullptr;
}

template<class T>
inline T* LispAssociatedHash<T>::LookUp(LispString * aString)
{
  LispInt bin = LispHashPtr(aString);
  LispInt i=0;
  // Find existing version of string
  for (i = iHashTable[bin].size()-1 ; i >= 0 ; i --)
  {
    // Get a reference to avoid creating a new object and calling the copy-constructor for it (performance optimization).
    LispStringSmartPtr &ptr = (((LAssoc<T>*)iHashTable[bin][i])->iString);
    if (ptr == aString)
    {
      return &((LAssoc<T>*)iHashTable[bin][i])->iData;
    }
  }
  return nullptr;
}

template<class T>
inline void LispAssociatedHash<T>::SetAssociation(const T& aData, LispString * aString)
{
  LispInt bin = LispHashPtr(aString);
  LispInt i;

  // Find existing version of string
  for (i=0;i<iHashTable[bin].size();i++)
  {
    // Get a reference to avoid creating a new object and calling the copy-constructor for it (performance optimization).
    LispStringSmartPtr &ptr = (((LAssoc<T>*)iHashTable[bin][i])->iString);
    if (ptr == aString)
    {
      //change existing version of association
      ((LAssoc<T>*)iHashTable[bin][i])->iData = aData;
      return;
    }
  }
  // Append a new string association
  iHashTable[bin].push_back(NEW LAssoc<T>(aString,aData));
  return;
}

template<class T>
inline void LispAssociatedHash<T>::Release(LispString * aString)
{
  LispInt bin = LispHashPtr(aString);
  LispInt i;

  // Find existing version of string
  for (i=0;i<iHashTable[bin].size();i++)
  {
    // Get a reference to avoid creating a new object and calling the copy-constructor for it (performance optimization).
    LispStringSmartPtr &ptr = (((LAssoc<T>*)iHashTable[bin][i])->iString);
    if (ptr == aString)
    {
      //change existing version of association
      delete ((LAssoc<T>*)iHashTable[bin][i]);
      iHashTable[bin][i] = nullptr;
      iHashTable[bin].erase(iHashTable[bin].begin() + i);
      return;
    }
  }
}


template<class T>
inline LispAssociatedHash<T>::~LispAssociatedHash()
{
  LispInt bin;
  for (bin=0;bin<KSymTableSize;bin++)
  {
    LispInt j;
    LispInt nritems = iHashTable[bin].size();
    for (j=0;j<nritems;j++)
    {
      delete ((LAssoc<T>*)iHashTable[bin][j]);
    }
  }
}


inline void HashByte(LispUnsLong& h, LispChar c)
{
    h=(h<<4)+c;
    LispUnsLong g = h&0xf0000000L;
    if (g)
    {
        h=h^(g>>24);
        h=h^g;
    }
}
#define HASHBIN(_h)    (LispInt)((_h)%KSymTableSize)


