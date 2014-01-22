from . import basereader
from data import graphics
from data.config import style

class YamlStyleReader(basereader.BaseYamlReader):
    """ Yaml reader for style types.

    Constants:
    VALUE_DEFAULT
    VALUE_HEIGHT
    VALUE_IMAGE
    VALUE_IMAGES
    VALUE_MAP
    VALUE_MAPPING
    VALUE_MAPPINGS
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_PATH
    VALUE_SPRITE
    VALUE_SPRITES
    VALUE_TILE_X
    VALUE_TILE_Y
    VALUE_TO
    VALUE_WIDTH
    VALUE_X
    VALUE_Y
    """

    VALUE_DEFAULT = 'default'
    VALUE_HEIGHT = 'height'
    VALUE_IMAGE = 'image'
    VALUE_IMAGES = 'images'
    VALUE_MAP = 'map'
    VALUE_MAPPING = 'mapping'
    VALUE_MAPPINGS = 'mappings'
    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_PATH = 'path'
    VALUE_SPRITE = 'sprite'
    VALUE_SPRITES = 'sprites'
    VALUE_TILE_X = 'tile_x'
    VALUE_TILE_Y = 'tile_y'
    VALUE_TO = 'to'
    VALUE_WIDTH = 'width'
    VALUE_X = 'x'
    VALUE_Y = 'y'

    def parse(self, root):
        """ Parse the style structure. Returns a graphics and a config
        style object. """

        namespace = self.read_req_string(root, self.VALUE_NAMESPACE)

        result_graphics = graphics.Graphics()
        result_graphics.tile_x = self.read_req_int(root, self.VALUE_TILE_X)
        result_graphics.tile_y = self.read_req_int(root, self.VALUE_TILE_Y)

        result_style = style.Style()
        if self.has(root, self.VALUE_IMAGES):
            result_style.images = self.__images(namespace, root)
        if self.has(root, self.VALUE_MAPPINGS):
            result_style.default_mapping, result_style.mappings = self.__mappings(namespace, root)
        if self.has(root, self.VALUE_SPRITES):
            result_style.sprites = self.__sprites(namespace, root)
        return result_graphics, result_style

    def __images(self, namespace, root):
        """ Parse images. """
        images = self.read_req_object(root, self.VALUE_IMAGES)
        namespace_list = [namespace, self.read_req_string(images, self.VALUE_NAMESPACE)]

        result = {}
        for image in self.read_object(images, self.VALUE_IMAGE, []):
            name = self.read_req_string(image, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            path = self.read_req_string(image, self.VALUE_PATH)
            result[id] = path
        return result

    def __mappings(self, namespace, root):
        """ Parse mappings. """
        mappings = self.read_req_object(root, self.VALUE_MAPPINGS)
        default_mapping = self.read_string(mappings, self.VALUE_DEFAULT, '')

        result = {}
        for mapping in self.read_object(mappings, self.VALUE_MAPPING, []):
            map = self.read_req_string(mapping, self.VALUE_MAP)
            to = self.read_req_string(mapping, self.VALUE_TO)
            result[map] = to
        return default_mapping, result

    def __sprites(self, namespace, root):
        """ Parse sprites. """
        sprites = self.read_req_object(root, self.VALUE_SPRITES)
        namespace_list = [namespace, self.read_req_string(sprites, self.VALUE_NAMESPACE)]

        default_image = self.read_string(sprites, self.VALUE_IMAGE, None)
        default_width = self.read_int(sprites, self.VALUE_WIDTH, None)
        default_height = self.read_int(sprites, self.VALUE_HEIGHT, None)

        result = {}
        for sprite in self.read_object(sprites, self.VALUE_SPRITE, []):
            name = self.read_req_string(sprite, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            image = self.read_string(sprite, self.VALUE_IMAGE, default_image)
            width = self.read_int(sprite, self.VALUE_WIDTH, default_width)
            height = self.read_int(sprite, self.VALUE_HEIGHT, default_height)
            x = self.read_req_int(sprite, self.VALUE_X)
            y = self.read_req_int(sprite, self.VALUE_Y)
            sprite_obj = style.Sprite(image, x, y, width, height)
            result[id] = sprite_obj
        return result