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
import numpy as np
from time import time

import im_util
import interest_point
import geometry

class RANSAC:
  """
  Find 2-view consistent matches using RANSAC
  """
  def __init__(self):
    self.params={}
    self.params['num_iterations']=500
    self.params['inlier_dist']=10
    self.params['min_sample_dist']=2

  def consistent(self, H, p1, p2):
    """
    Find interest points that are consistent with 2D transform H

    Inputs: H=homography matrix (3,3)
            p1,p2=corresponding points in images 1,2 of shape (2, N)

    Outputs: cons=list of inliers indicated by true/false (num_points)

    Assumes that H maps from 1 to 2, i.e., hom(p2) ~= H hom(p1)
    """

    cons = np.zeros((p1.shape[1]))
    inlier_dist = self.params['inlier_dist']

    """
    ************************************************
    *** TODO: write code to check consistency with H
    ************************************************
    """

    p1h = geometry.hom(p1)
    p2h = geometry.hom(p2)
    applied = np.dot(H, p1h)

    for i in range(p1.shape[1]):
      if np.linalg.norm(applied[:,i] - p2h[:,i]) < inlier_dist:
        cons[i] = 1

    """
    ************************************************
    """

    return cons

  def compute_similarity(self,p1,p2):
    """
    Compute similarity transform between pairs of points

    Input: p1,p2=arrays of coordinates (2, 2)

    Output: Similarity matrix S (3, 3)

    Assume S maps from 1 to 2, i.e., hom(p2) = S hom(p1)
    """

    S = np.eye(3,3)

    """
    ****************************************************
    *** TODO: write code to compute similarity transform
    ****************************************************
    """

    p1h = geometry.hom(p1)
    p2h = geometry.hom(p2)
    X_pseudo_inverse = np.linalg.pinv(p1h)
    S = np.dot(p2h, X_pseudo_inverse)

    """
    ****************************************************
    """

    return S

  def ransac_similarity(self, ip1, ipm):
    """
    Find 2-view consistent matches under a Similarity transform

    Inputs: ip1=interest points (2, num_points)
            ipm=matching interest points (2, num_points)
            ip[0,:]=row coordinates, ip[1, :]=column coordinates

    Outputs: S_best=Similarity matrix (3,3)
             inliers_best=list of inliers indicated by true/false (num_points)
    """
    S_best=np.eye(3,3)
    inliers_best=[]

    """
    *****************************************************
    *** TODO: use ransac to find a similarity transform S
    *****************************************************
    """

    num_iterations = self.params['num_iterations']
    min_sample_dist = self.params['min_sample_dist']
    num_sample_points = 3
    num_points = ip1.shape[1]

    rng = np.random.default_rng(6666)

    def get_valid_samples(points, ids):
      valid_ids = [ids[0]]
      for i in range(1, points.shape[1]):
        if np.min(np.linalg.norm(points[:,[ids[i]]] - points[:,valid_ids], axis=0)) > min_sample_dist:
          valid_ids.append(ids[i])
        if len(valid_ids) >= num_sample_points:
          break
      return valid_ids
    
    def get_random_samples(rng, num_points, num_samples):
      return rng.choice(num_points, num_samples, replace=False)

    for _ in range(num_iterations):
      id1 = get_valid_samples(ip1, get_random_samples(rng, num_points, num_sample_points + 2))
      maybe_inliers = ip1[:,id1]
      maybe_matches = ipm[:,id1]
      maybe_S = self.compute_similarity(maybe_inliers, maybe_matches)
      maybe_inliers = self.consistent(maybe_S, ip1, ipm)
      if np.sum(maybe_inliers) >= np.sum(inliers_best):
        inliers_best = maybe_inliers
        S_best = maybe_S
    inliers_best = inliers_best.astype(bool).tolist()
    """
    *****************************************************
    """

    return S_best, inliers_best
