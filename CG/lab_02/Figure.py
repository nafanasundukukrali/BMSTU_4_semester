import math
from copy import deepcopy
from config import *


class Figure:
    a = 100
    b = 50

    def __init__(self):
        self._center = []
        self._header = []
        self._tube = []
        self._wheels_base = []
        self._wheels = []
        self._reverse_state = []

    def _clear(self):
        self.__dict__.clear()
        self.__init__()

    def check_free_status(self):
        return not self._header

    def draw_base_figure(self, start_width_move, start_height_move):
        self._clear()
        self._center = [[0.0, 0.0]]
        self._calc_header_cords()
        self._calc_tube_cords()
        self._calc_wheels_cords()

        self._body_rect = [[BASE_WIDTH, 0], [BASE_WIDTH, BASE_HEIGHT], [-BASE_WIDTH, BASE_HEIGHT], [-BASE_WIDTH, 0]]

        self.move_figure(start_width_move, start_height_move)
        self._reverse_action = []

    def _calc_header_cords(self):
        i = 0

        while i * math.pi <= math.pi:
            self._header.append(self._get_ellipse_y_cords(i, BASE_WIDTH, -MAIN_ELLIPSE_HEIGHT))
            i += 0.001

        self._header.append([BASE_WIDTH, 0])

    def _calc_tube_cords(self):
        tube_start = self._get_ellipse_y_cords(3 / 4, BASE_WIDTH, -MAIN_ELLIPSE_HEIGHT)
        tube_end = self._get_ellipse_y_cords(2 / 3, BASE_WIDTH, -MAIN_ELLIPSE_HEIGHT)

        self._tube = []

        for i in range(3):
            self._tube.insert(0, tube_start.copy())
            self._tube.append(tube_end.copy())

        self._move_point(self._tube[1], 0, -TUBE_HEIGHT)
        self._move_point(self._tube[2], TUBE_HEIGHT, -TUBE_HEIGHT)
        self._move_point(self._tube[3], self._tube[2][0] - self._tube[3][0], -TUBE_HEIGHT / 2)
        self._move_point(self._tube[4], 0, -TUBE_HEIGHT / 2)

    def _calc_wheels_cords(self):
        self._wheels_base.append([-WHEELS_WIDTH, BASE_HEIGHT + WHEELS_HEIGHT])
        self._wheels_base.append([WHEELS_WIDTH, BASE_HEIGHT + WHEELS_HEIGHT])

        half_of_circle_cords = []

        i = math.pi / 6
        while i >= math.pi / 8:
            half_of_circle_cords.append(self._get_ellipse_y_cords(i,
                                                                  SMALL_ELLIPSE_WIDTH / 2,
                                                                  WHEELS_HEIGHT / 2,
                                                                  WHEELS_WIDTH, BASE_HEIGHT + WHEELS_HEIGHT / 2))
            i -= 0.001

        i = 2 * math.pi

        while i > 7 / 4 * math.pi:
            half_of_circle_cords.append(self._get_ellipse_y_cords(i,
                                                                  SMALL_ELLIPSE_WIDTH / 2,
                                                                  WHEELS_HEIGHT / 2,
                                                                  WHEELS_WIDTH, BASE_HEIGHT + WHEELS_HEIGHT / 2))
            i -= 0.01

        self._wheels_base += half_of_circle_cords
        self._wheels_base.append([WHEELS_WIDTH, BASE_HEIGHT])
        self._wheels_base.append([-WHEELS_WIDTH, BASE_HEIGHT])

        new_half_of_circle_cords = deepcopy(half_of_circle_cords)

        self._modification_dot_array(new_half_of_circle_cords, self._move_point, 0, 0)
        self._modification_dot_array(new_half_of_circle_cords, self._scale_point, 0, 0, -1, 1)
        self._wheels_base += new_half_of_circle_cords[::-1]
        self._calc_wheel_circles()

    def _calc_wheel_circles(self):
        step = (SMALL_ELLIPSE_WIDTH + WHEELS_WIDTH * 2) / 10 / 2
        start = -WHEELS_WIDTH - SMALL_ELLIPSE_WIDTH / 2 + step * 2

        for i in range(5):
            new_circle = []
            t = 0

            while t < math.pi * 2:
                new_circle.append(self._get_ellipse_y_cords(t, step, step, start, BASE_HEIGHT + WHEELS_HEIGHT / 2))
                t += 0.01

            self._wheels.append(new_circle)
            start += step * 4

    @staticmethod
    def _get_ellipse_y_cords(t, a, b, xm=0, ym=0):
        return [a * math.cos(t * math.pi) + xm, b * math.sin(t * math.pi) + ym]

    def move_figure(self, dx, dy):
        if abs(dx) < EPSILON and abs(dy) < EPSILON:
            return ERRORS.ERROR_MODIFICATION_PARAMS

        self._reverse_data_copy()

        self._modification_dot_array(self._center, self._move_point, dx, dy)
        self._modification_dot_array(self._body_rect, self._move_point, dx, dy)
        self._modification_dot_array(self._header, self._move_point, dx, dy)
        self._modification_dot_array(self._tube, self._move_point, dx, dy)
        self._modification_dot_array(self._wheels_base, self._move_point, dx, dy)

        for circle in self._wheels:
            self._modification_dot_array(circle, self._move_point, dx, dy)

    def scale_figure(self, xm, ym, kx, ky):
        self._reverse_data_copy()

        self._modification_dot_array(self._center, self._scale_point, xm, ym, kx, ky)
        self._modification_dot_array(self._body_rect, self._scale_point, xm, ym, kx, ky)
        self._modification_dot_array(self._header, self._scale_point, xm, ym, kx, ky)
        self._modification_dot_array(self._tube, self._scale_point, xm, ym, kx, ky)
        self._modification_dot_array(self._wheels_base, self._scale_point, xm, ym, kx, ky)

        for circle in self._wheels:
            self._modification_dot_array(circle, self._scale_point, xm, ym, kx, ky)

    def rotate_figure(self, xc, yc, alpha):
        self._reverse_data_copy()

        self._modification_dot_array(self._center, self._rotate_point, xc, yc, alpha)
        self._modification_dot_array(self._body_rect, self._rotate_point, xc, yc, alpha)
        self._modification_dot_array(self._header, self._rotate_point, xc, yc, alpha)
        self._modification_dot_array(self._tube, self._rotate_point, xc, yc, alpha)
        self._modification_dot_array(self._wheels_base, self._rotate_point, xc, yc, alpha)

        for circle in self._wheels:
            self._modification_dot_array(circle, self._rotate_point, xc, yc, alpha)

    def reverse_figure(self):
        self._center = deepcopy(self._reverse_action[0])
        self._body_rect = deepcopy(self._reverse_action[1])
        self._header = deepcopy(self._reverse_action[2])
        self._tube = deepcopy(self._reverse_action[3])
        self._wheels_base = deepcopy(self._reverse_action[4])
        self._wheels = deepcopy(self._reverse_action[5])

        self._reverse_action = []

    def _reverse_data_copy(self):
        self._reverse_action = [deepcopy(self._center),
                                deepcopy(self._body_rect),
                                deepcopy(self._header),
                                deepcopy(self._tube),
                                deepcopy(self._wheels_base),
                                deepcopy(self._wheels)]

    @staticmethod
    def _modification_dot_array(array, function, *args):
        for i in range(len(array)):
            function(array[i], *args)

    @staticmethod
    def _move_point(dot, dx, dy):
        dot[0] = dot[0] + dx
        dot[1] = dot[1] + dy

    @staticmethod
    def _scale_point(dot, xm, ym, kx, ky):
        dot[0] = kx * dot[0] + (1 - kx) * xm
        dot[1] = ky * dot[1] + (1 - ky) * ym

    @staticmethod
    def _rotate_point(dot, xc, yc, alpha):
        def convert_cords_to_radian():
            return alpha * math.pi / 180

        alpha = convert_cords_to_radian()

        dot[0] = xc + (dot[0] - xc) * math.cos(alpha) + (dot[1] - yc) * math.sin(alpha)
        dot[1] = yc - (dot[0] - xc) * math.sin(alpha) + (dot[1] - yc) * math.cos(alpha)

    def check_reverse_figure_ability(self):
        return not self._reverse_action

    def check_figure_free_status(self):
        return not self._header

    def get_center_cords(self):
        return self._center[0]

    def get_wheels_base(self):
        return self._wheels_base

    def get_tube(self):
        return self._tube

    def get_body_rect(self):
        return self._body_rect

    def get_header(self):
        return self._header

    def get_wheels(self):
        return self._wheels
