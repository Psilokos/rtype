//
// ComponentTypes.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 20:03:54 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 18 17:16:17 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "CompileTime.hpp"
#include "ComponentTypeID.hpp"
#include "ComponentTypePair.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    template<typename...> struct	ComponentTypes;

    template<ComponentTypeID... componentTypes, typename... Components>
    struct	ComponentTypes<ComponentTypePair<componentTypes, Components>...>
    {
      template<unsigned idx>
      struct	GetComponentTypePair
      {
	template<unsigned, typename, typename = void> struct _GetComponentTypePair;

	template<unsigned _idx, typename CTPair, typename... CTPairs>
	struct	_GetComponentTypePair<_idx, ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<_idx>::type>
	{
	  typedef typename _GetComponentTypePair<_idx - 1, ct::TypesWrapper<CTPairs...>>::Type	Type;
	};

	template<unsigned _idx, typename CTPair, typename... CTPairs>
	struct	_GetComponentTypePair<_idx, ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<!_idx>::type>
	{
	  typedef CTPair	Type;
	};

	typedef typename _GetComponentTypePair<idx, ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::Type	Type;
      };

      template<ComponentTypeID typeID>
      struct	GetComponentType
      {
	template<typename, typename = void> struct _GetComponentType;

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentType<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<typeID != CTPair::typeID>::type>
	{
	  typedef typename _GetComponentType<ct::TypesWrapper<CTPairs...>>::Type	Type;
	};

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentType<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<typeID == CTPair::typeID>::type>
	{
	  typedef typename CTPair::Type		Type;
	};

	typedef typename _GetComponentType<ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::Type	Type;
      };

      template<typename Component>
      struct	GetComponentTypeID
      {
	template<typename, typename = void> struct	_GetComponentTypeID;

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentTypeID<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<!std::is_same<typename std::decay<Component>::type, typename CTPair::Type>::value>::type>
	{
	  static constexpr ComponentTypeID	typeID = _GetComponentTypeID<ct::TypesWrapper<CTPairs...>>::typeID;
	};

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentTypeID<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<std::is_same<typename std::decay<Component>::type, typename CTPair::Type>::value>::type>
	{
	  static constexpr ComponentTypeID	typeID = CTPair::typeID;
	};

	static constexpr ComponentTypeID	typeID = _GetComponentTypeID<ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::typeID;
      };
    };
  }
}
