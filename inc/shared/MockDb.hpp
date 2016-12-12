#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <vector>

namespace ecs {
  namespace database {
    /**
    ** \brief Mock Component.
    **
    ** This mock Component class store its data in a Map of string, with the attribute name as key.
    */
    class Component {
      public:
        /**
        ** \brief Component UID.
        */
        static int			id;

        /**
        ** \brief Default constructor. Build an empty component with a new UID.
        */
        Component();

        /**
        ** \brief Copy constructor. Create new component by setting it's UID, and copying src attribute name.
        **
        ** \param [in] src The component to be copied.
        */
        Component(Component const &src);

        /**
        ** \brief To be used constructor. Create new component by setting it's UID, and it's attribute name.
        **
        ** \param [in] attribute vector of string to be used as attribute name. Use of initializer list is highly advised.
        */
        Component(std::vector<std::string> const &&attribute);

        /**
        ** \brief Component ID getter.
        **
        ** \return Return the Component UID.
        */
        int				getId() const { return _id; }

        /**
        ** \brief Get a attribute value.
        **
        ** \tparam T The type of the value to be returned.
        **
        ** \param [in] name Name of the attribute to be retreived.
        **
        ** \return Return the value of the asked attribute.
        */
        template<typename T>
          T				getAttr(std::string name) const;

        /**
        ** \brief set a attribute value.
        **
        ** \tparam T The type of the value to be stored.
        **
        ** \param [in] name Name of the attribute to be set.
        ** \param [in] value Value to be set.
        **
        ** \return This function does not return.
        */
        template<typename T>
          void				setAttr(std::string name, T value);
      private:
        int					_id;
        std::map<std::string, std::string>	_attr;
    };

    template<typename T>
      T				Component::getAttr(std::string name) const {
        std::stringstream		ss;
        T			ret;

        ss.str(_attr.at(name));
        ss >> ret;
        return ret;
      }

    template<typename T>
      void			Component::setAttr(std::string name, T value) {
        std::stringstream		ss;

        ss << value;
        _attr[name] = ss.str();
      }

    /**
    ** \brief Mock Entity.
    **
    ** This mock Entty class store its Component in a Map of pointer to Component, with the Component name as key.
    ** Should be used only with mock Component.
    */
    class Entity {
      public:
        /**
        ** \brief Entity UID.
        */
        static int				id;

        /**
        ** \brief Entity Constructor. Should NOT be called.
        */
        Entity();

        /**
        ** \brief Return Entity UID.
        **
        ** \return Return entity UID.
        */
        int					getId() const { return _id; }
        /**
        ** \brief Add a Component in the Entity. Should not be called.
        **
        ** \param [in] cname Name of the component to be added.
        ** \param [in] cmp Pointer on the Component to be added.
        **
        ** \return If no error happened, 0 is returned.
        */
        int					addComponent(std::string const &, Component *);
        /**
        ** \brief Retreive a component inside the Entity.
        **
        ** \param [in] cname Name of the Component to be retreived.
        **
        ** \return Return the Component if found.
        */
        Component				*getComponent(std::string const &);

      private:
        int					_id;
        std::map<std::string, Component *>	_components;

      friend class IDataBase;
    };

    /**
    ** \brief Mock IDataBase.
    **
    ** Event tho it has the name of an interface, it's not.\n
    ** It was only to be able to compile properly.
    ** It contains several function to add entity, bind component, and retreive Entity.
    **
    ** The database contains maps of Entity and Component identified by their UID.\n
    ** It also has a map containing Components name, identified by their Component UID (to be able to have several Component with the same name).
    ** Last but not least, this database contains a vector of pair mapping an Entity UID to a Component UID.
    */
    class IDataBase {
      public:
        /**
        ** \brief Retreive an Entity.
        **
        ** \param [in] id The UID of the Entity to be retreived.
        **
        ** \return Return a pointer on the Entity if no error happened.
        */
        Entity					*getEntityById(int id);

        /**
        ** \brief Retreive all Entity containing a component identified by the cname arg.
        **
        ** \param [in] cname The name of the Components for which an Entity has to be retreived.
        **
        ** \return Return a vector of found Entity pointer's.
        */
        std::vector<Entity *>			getEntitiesWithComponents(std::string const &cname);

        /**
        ** \brief Retreive all Entity containing a component identified by the cname arg, whose value match the vector of values given.
        **
        ** \tparam T type of the values to be compared.
        **
        ** \param [in] cname The name of the Components for which an Entity has to be retreived.
        ** \param [in] values vector of pair<name, value> representing the component. Use of initializer list is highly advised.
        **
        ** \return Return a vector of found Entity pointer's.
        */
        template<typename T>
        std::vector<Entity *>			getEntitiesWithComponentsValue(std::string const &cname, std::vector<std::pair<std::string, T>> &&values);

        /**
        ** \brief Create a new Entity, and add it to the database.
        **
        ** \return Return the newly created Entity UID.
        */
        int					addEntity();

        /**
        ** \brief Remove an Entity and all it's Components.
        **
        ** \param [in] eid UID of the Entity to be removed.
        */
        void					removeEntity(int eid);

        /**
        ** \brief Bind given component to an Entity identified by it's UID.
        **
        ** \param [in] cname Component name.
        ** \param [in] cmp pointer on Component to be add to the DB and the Entity.
        ** \param [in] eid UID of the Entity on which cmp has to be bound.
        **
        ** \return Return 0 if no error happened.
        */
        int					bindComponent(std::string const &cname, Component *cmp, int eid);

      private:
        std::map<int, Entity *>			_entities;
        std::map<int, Component *>		_components;
        std::map<int, std::string>		_cname;
        std::vector<std::pair<int, int>>	_map;
    };

    template<typename T>
      std::vector<Entity *>		IDataBase::getEntitiesWithComponentsValue(std::string const &cname, std::vector<std::pair<std::string, T>> &&values) {
        std::vector<Entity *>		ret;
        Component			*cmp;
        int				cid;
        int				eid;
        bool				match;
        T				val;

        for (auto cmpnents : _cname) {
          if (cmpnents.second == cname) {
            match = true;
            cid = cmpnents.first;
            cmp = _components.at(cid);
            for (auto attrs : values) {
              val = cmp->getAttr<T>(attrs.first);
              if (val != attrs.second) {
                match = false;
                break ;
              }
            }
            if (match) {
              for (auto mp : _map)
                if (mp.second == cid)
                  ret.push_back(_entities.at(mp.first));
            }
          }
        }
        return ret;
      }
  } // namespace database
} // namespace ecs
