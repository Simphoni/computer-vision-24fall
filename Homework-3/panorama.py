# Copyright 2017 Google Inc.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# https://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os.path
from time import time
import numpy as np

import im_util
import match
import geometry
import ransac
import render

class PanoramaStitcher:
  """
  Stitch a panorama from input images
  """
  def __init__(self, images, params={}):
    self.images = images
    num_images = len(images)
    self.matches = [[None]*num_images for _ in range(num_images)]
    self.num_matches = np.zeros((num_images, num_images))
    self.stitch_order = []
    self.R_matrices = [None]*num_images
    self.params = params
    self.params.setdefault('fov_degrees', 45)
    self.params.setdefault('draw_interest_points', False)
    self.params.setdefault('draw_matches', False)
    self.params.setdefault('draw_pairwise_warp', False)
    self.params.setdefault('results_dir', os.path.expanduser('~/results/tmp/'))

  def stitch(self):
    """
    Match images and perform alignment
    """
    self.match_images()
    self.align_panorama()

  def match_images(self):
    """
    Match images
    """
    im=match.ImageMatcher(self.params)
    self.matches, self.num_matches = im.match_images(self.images)

  def align_panorama(self):
    """
    Perform global alignment
    """
    # FORNOW identity rotations
    num_images = len(self.images)
    for i in range(num_images):
      self.R_matrices[i]=np.eye(3,3)

    """
    ***************************************************************
    *** TODO write code to compute a global rotation for each image
    ***************************************************************
    """


    """
    ***************************************************************
    """

  def render(self, render_params={}):
    """
    Render output panorama
    """
    print('[ render panorama ]')
    t0=time()
    P_matrices = self.get_projection_matrices()
    pano_im=render.render_spherical(self.images, P_matrices, render_params)
    t1=time()
    print(' % .2f secs' % (t1-t0))

    return pano_im

  def get_projection_matrices(self):
    """
    Return projection matrices P such that u~=PX
    """
    num_images = self.num_matches.shape[0]
    P_matrices = [None]*num_images
    for i in range(num_images):
      Ki = geometry.get_calibration(self.images[i].shape, self.params['fov_degrees'])
      P_matrices[i] = np.dot(Ki, self.R_matrices[i])

    return P_matrices

