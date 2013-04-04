/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef DYNAMICFACTORY_H_INCLUDED
#define DYNAMICFACTORY_H_INCLUDED

#include <map>
#include <string>
#include <iostream>

class TestRegistrar;

template <class DynamicType>
class DynamicFactory
{
public:

    typedef DynamicType *DynamicTypeCtor();
    typedef std::map<std::string, DynamicTypeCtor*, std::less<std::string> >
            DynamicTypeFactoryMap;
    typedef std::pair<std::string, DynamicTypeCtor*> DynamicTypeTemplate;

    static DynamicFactory &getInstance();

    void insert(const DynamicTypeTemplate &testTemplate);

    void registerAll(TestRegistrar *registrar);

    void clear();

private:

    // Application of Singleton Pattern
    DynamicFactory() {};
    DynamicFactory(const DynamicFactory &other);   // Unimplemented
    void operator=(const DynamicFactory &other);   // Unimplemented

    DynamicTypeFactoryMap factoryMap;
};

template <class DynamicType>
DynamicFactory<DynamicType> &DynamicFactory<DynamicType>::getInstance()
{
    static DynamicFactory<DynamicType> instance;
    return instance;
}

template <class DynamicType>
void DynamicFactory<DynamicType>::insert(const DynamicTypeTemplate &typeTemplate)
{
    factoryMap.insert(typeTemplate);
}

template <class DynamicType>
void DynamicFactory<DynamicType>::registerAll(TestRegistrar *registrar)
{
    typename DynamicTypeFactoryMap::iterator iter = factoryMap.begin();
    while(iter != factoryMap.end())
    {
        std::cout << iter->first << std::endl;
        iter->second()->register_all(registrar);
        ++iter;
    }
}

template <class DynamicType>
void DynamicFactory<DynamicType>::clear()
{
    factoryMap.clear();
}

#endif // DYNAMICFACTORY_H_INCLUDED
