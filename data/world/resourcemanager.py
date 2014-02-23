class ResourceManager:
    """ Manages resources in the world and finds them.

    Member:
    heuristic -- Heuristic which calculates the distance of two points.
    region -- The region of the manager (data.world.region).
    _entity_resource -- Maps entity ids to resource types (dict).
    _locked -- List of locked entity (list):
    _resource_entity -- Maps resource type to list of entities (dict).
    """

    def __init__(self, heuristic, entity_config):
        """ Test:
        >>> from ai import pathfinding
        >>> from data.config import entity as config
        >>> heuristic = pathfinding.EuclideanDistance()
        >>> entity_config = config.Entity()
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity1'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity2'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource2'
        >>> entity_config.statics['entity3'] = entity
        >>> rm = ResourceManager(heuristic, entity_config)
        >>> len(rm._entity_resource)
        3
        >>> rm._entity_resource['entity1']
        'resource1'
        >>> rm._entity_resource['entity2']
        'resource1'
        >>> rm._entity_resource['entity3']
        'resource2'
        """
        self.heuristic = heuristic
        self.region = None
        self._locked = []
        self._resource_entity = {}

        self._entity_resource = {}
        for key, entity in entity_config.statics.items():
            if entity.resource:
                self._entity_resource[key] = entity.resource.type

    def add_entity(self, entity):
        """ Add entity to resource manager.

        Test:
        >>> from ai import pathfinding
        >>> from data.config import entity as config
        >>> from data.world import staticentity
        >>> heuristic = pathfinding.EuclideanDistance()
        >>> entity_config = config.Entity()
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity1'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity2'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource2'
        >>> entity_config.statics['entity3'] = entity
        >>> rm = ResourceManager(heuristic, entity_config)
        >>> entity1 = staticentity.StaticEntity('entity1')
        >>> rm.add_entity(entity1)
        >>> entity2 = staticentity.StaticEntity('entity2')
        >>> rm.add_entity(entity2)
        >>> entity3 = staticentity.StaticEntity('entity3')
        >>> rm.add_entity(entity3)
        >>> len(rm._resource_entity)
        2
        >>> rm._resource_entity['resource1'][0] == entity1
        True
        >>> rm._resource_entity['resource1'][1] == entity2
        True
        >>> rm._resource_entity['resource2'][0] == entity3
        True
        """
        if entity.id not in self._entity_resource:
            return
        resource = self._entity_resource[entity.id]
        self._resource_entity.setdefault(resource, []).append(entity)

    def find_resource(self, resource_type, pos):
        """ Finds a nearby resource of the given type. Locks and returns the
        entity containing this resource. """
        entities = self._resource_entity[resource_type]
        result = None
        min_distance = None
        for entity in entities:
            distance = self.heuristic.distance(pos, self.region.get_pos(entity))
            if min_distance is None or distance < min_distance:
                min_distance = distance
                result = entity
        if result:
            self.remove_entity(result)
            self._locked.append(result)
        return result

    def release_resource(self, entity):
        """ Releases a locked resource.

        Test:
        >>> from ai import pathfinding
        >>> from data.config import entity as config
        >>> from data.world import staticentity
        >>> heuristic = pathfinding.EuclideanDistance()
        >>> entity_config = config.Entity()
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity1'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity2'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource2'
        >>> entity_config.statics['entity3'] = entity
        >>> rm = ResourceManager(heuristic, entity_config)
        >>> entity1 = staticentity.StaticEntity('entity1')
        >>> rm._locked.append(entity1)
        >>> len(rm._locked)
        1
        >>> len(rm._resource_entity)
        0
        >>> rm.release_resource(entity1)
        >>> len(rm._locked)
        0
        >>> len(rm._resource_entity)
        1
        """
        if entity in self._locked:
            self._locked.remove(entity)
            self.add_entity(entity)

    def remove_entity(self, entity):
        """ Remove entity from resource manager.

        Test:
        >>> from ai import pathfinding
        >>> from data.config import entity as config
        >>> from data.world import staticentity
        >>> heuristic = pathfinding.EuclideanDistance()
        >>> entity_config = config.Entity()
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity1'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource1'
        >>> entity_config.statics['entity2'] = entity
        >>> entity = config.StaticEntity()
        >>> entity.resource = config.Resource()
        >>> entity.resource.type = 'resource2'
        >>> entity_config.statics['entity3'] = entity
        >>> rm = ResourceManager(heuristic, entity_config)
        >>> entity1 = staticentity.StaticEntity('entity1')
        >>> rm._locked.append(entity1)
        >>> len(rm._locked)
        1
        >>> len(rm._resource_entity)
        0
        >>> rm.remove_entity(entity1)
        >>> len(rm._locked)
        0
        >>> len(rm._resource_entity['resource1'])
        0
        >>> rm.add_entity(entity1)
        >>> len(rm._resource_entity['resource1'])
        1
        >>> rm.remove_entity(entity1)
        >>> len(rm._resource_entity['resource1'])
        0
        """
        if entity.id not in self._entity_resource:
            return
        self.release_resource(entity)
        resource = self._entity_resource[entity.id]
        self._resource_entity.setdefault(resource, []).remove(entity)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()