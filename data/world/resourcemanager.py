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
        self.heuristic = heuristic
        self.region = None
        self._locked = []
        self._resource_entity = {}

        self._entity_resource = {}
        for key, entity in entity_config.statics.items():
            if entity.resource:
                self._entity_resource.setdefault(key, []).append(entity.resource.type)

    def add_entity(self, entity):
        """ Add entity to resource manager. """
        if entity.id not in self._entity_resource:
            return
        resources = self._entity_resource[entity.id]
        for resource in resources:
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
        """ Releases a locked resource. """
        if entity in self._locked:
            self._locked.remove(entity)
            self.add_entity(entity)

    def remove_entity(self, entity):
        """ Remove entity from resource manager. """
        if entity.id not in self._entity_resource:
            return
        self.release_resource(entity)
        resources = self._entity_resource[entity.id]
        for resource in resources:
            self._resource_entity.setdefault(resource, []).remove(entity)