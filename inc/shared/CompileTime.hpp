//
// CompileTime.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 10 05:47:59 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sun Dec 11 00:17:38 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

namespace	compile_time
{
  //! \brief wrap a set of types
  template<typename...> struct	TypesWrapper;

  template<char const *...> struct	StringsWrapper;

  template<unsigned, unsigned, void *, char const *...>
  struct	_GetString;

  template<unsigned curIdx, unsigned idx, typename std::enable_if<curIdx == idx, void *>::type _vp, char const * string, char const *... strings>
  struct	_GetString<curIdx, idx, _vp, string, strings...>
  {
    static constexpr auto	value = string;
  };

  template<unsigned curIdx, unsigned idx, typename std::enable_if<curIdx < idx, void *>::type _vp, char const * string, char const *... strings>
	   struct	_GetString<curIdx, idx, _vp, string, strings...>
	   {
	     static constexpr auto	value = _GetString<curIdx + 1, idx, nullptr, strings...>::value;
	   };

  template<unsigned idx, char const *... strings>
  struct	GetString
  {
    static constexpr auto	value = _GetString<0, idx, nullptr, strings...>::value;
  };

  template<char const * s1, char const * s2>
  constexpr bool
  strcmp(typename std::enable_if<s1 == s2, void *>::type = 0)
  {
    return true;
  }

  template<char const * s1, char const * s2>
  constexpr bool
  strcmp(typename std::enable_if<s1 != s2 && (*s1 && *s2 ? *s1 == *s2 && strcmp<s1 + 1, s2 + 1>() : !*s1 && !*s2), void *>::type = 0)
  {
    return true;
  }

  template<char const * s1, char const * s2>
  constexpr bool
  strcmp(typename std::enable_if<s1 != s2 && *s1 ^ *s2, void *>::type = 0)
  {
    return false;
  }

  template<unsigned idx, char const * s1, char const *... s>
  constexpr unsigned
  _getIdx(std::true_type)
  {
    return idx - 1;
  }

  template<unsigned idx, char const *s1, char const *s2, char const *... s>
  constexpr unsigned
  _getIdx(std::false_type)
  {
    return _getIdx<idx + 1, s1, s...>(std::integral_constant<bool, strcmp<s1, s2>()>());
  }

  template<char const * toFind, char const *... list>
  constexpr unsigned
  getIdx(void)
  {
    return _getIdx<0, toFind, list...>(std::false_type());
  }
}

namespace	ct = compile_time;
