from . import basereader
from data.config import style

class YamlStyleReader(basereader.BaseYamlReader):
    """ Yaml reader for style types.

    Constants:
    CHANCE
    DEFAULT
    IMAGE
    IMAGES
    MAP
    MAPPING
    MAPPINGS
    MULTIPLE
    NAME
    NAMESPACE
    PATH
    SPRITE
    SPRITES
    TILE_X
    TILE_Y
    TO
    X
    Y
    """

    CHANCE = 'chance'
    DEFAULT = 'default'
    IMAGE = 'image'
    IMAGES = 'images'
    MAP = 'map'
    MAPPING = 'mapping'
    MAPPINGS = 'mappings'
    MULTIPLE = 'multiple'
    NAME = 'name'
    NAMESPACE = 'namespace'
    PATH = 'path'
    SPRITE = 'sprite'
    SPRITES = 'sprites'
    TILE_X = 'tile_x'
    TILE_Y = 'tile_y'
    TO = 'to'
    X = 'x'
    Y = 'y'

    def parse(self, root, data):
        """ Parse the style structure. Writes the parsed information into the
        data object. """
        namespace = self.read_req_string(root, self.NAMESPACE)

        data.graphics.tile_x = self.read_int(root, self.TILE_X, data.graphics.tile_x)
        data.graphics.tile_y = self.read_int(root, self.TILE_Y, data.graphics.tile_y)

        if self.has(root, self.IMAGES):
            self.__images(namespace, root, data)
        if self.has(root, self.MAPPINGS):
            self.__mappings(namespace, root, data)
        if self.has(root, self.SPRITES):
            self.__sprites(namespace, root, data)

    def __images(self, namespace, root, data):
        """ Parse images. """
        images = self.read_req_object(root, self.IMAGES)
        namespace_list = [namespace, self.read_req_string(images, self.NAMESPACE)]

        for image in self.read_object(images, self.IMAGE, []):
            name = self.read_req_string(image, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            path = self.read_req_string(image, self.PATH)
            image_obj = style.Image()
            image_obj.path = path
            data.config.style.images[id] = image_obj

    def __mappings(self, namespace, root, data):
        """ Parse mappings. """
        mappings = self.read_req_object(root, self.MAPPINGS)
        data.config.style.default_mapping = self.read_string(mappings, self.DEFAULT, '')

        for mapping in self.read_object(mappings, self.MAPPING, []):
            map = self.read_req_string(mapping, self.MAP)
            to = self.read_req_string(mapping, self.TO)
            data.config.style.mappings[map] = to

    def __sprites(self, namespace, root, data):
        """ Parse sprites. """
        sprites = self.read_req_object(root, self.SPRITES)
        namespace_list = [namespace, self.read_req_string(sprites, self.NAMESPACE)]

        default_image = self.read_string(sprites, self.IMAGE, None)

        for sprite in self.read_object(sprites, self.SPRITE, []):
            name = self.read_req_string(sprite, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            image = self.read_string(sprite, self.IMAGE, default_image)
            if self.has(sprite, self.MULTIPLE):
                sprite_obj = []
                for multiple in self.read_object(sprite, self.MULTIPLE, []):
                    x = self.read_req_int(multiple, self.X)
                    y = self.read_req_int(multiple, self.Y)
                    multiple_obj = style.Sprite(image, x, y)
                    multiple_obj.chance = self.read_req_float(multiple, self.CHANCE)
                    sprite_obj.append(multiple_obj)
            else:
                x = self.read_req_int(sprite, self.X)
                y = self.read_req_int(sprite, self.Y)
                sprite_obj = style.Sprite(image, x, y)
            data.config.style.sprites[id] = sprite_obj