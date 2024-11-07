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

import interest_point
import ransac

class ImageMatcher:
  """
  Find geometrically consistent matches in a set of images
  """
  def __init__(self, params={}):
    self.params=params
    self.params.setdefault('draw_interest_points', False)
    self.params.setdefault('draw_matches', False)
    self.params.setdefault('results_dir', os.path.expanduser('~/results/tmp/'))

  def match_images(self, images):
    """
    Find geometrically consistent matches between images
    """
    # extract interest points and descriptors
    print('[ find interest points ]')
    t0=time()
    interest_points=[]
    descriptors=[]
    ip_ex = interest_point.InterestPointExtractor()
    desc_ex = interest_point.DescriptorExtractor()
    num_images = len(images)

    for i in range(num_images):
      im = images[i]
      img = np.mean(im, 2, keepdims=True)
      ip = ip_ex.find_interest_points(img)
      print(' found '+str(ip.shape[1])+' interest points')
      interest_points.append(ip)
      desc = desc_ex.get_descriptors(img, ip)
      descriptors.append(desc)
      if (self.params['draw_interest_points']):
        interest_point.draw_interest_points_file(im, ip, self.params['results_dir']+'/ip'+str(i)+'.jpg')

    t1=time()
    print(' % .2f secs ' % (t1-t0))

    # match descriptors and perform ransac
    print('[ match descriptors ]')
    matches = [[None]*num_images for _ in range(num_images)]
    num_matches = np.zeros((num_images, num_images))

    t0=time()
    rn = ransac.RANSAC()

    for i in range(num_images):
      ipi = interest_points[i]
      print(' image '+str(i))
      for j in range(num_images):
        if (i==j):
          continue

        matchesij = desc_ex.match_descriptors(descriptors[i],descriptors[j])
        ipm = interest_points[j][:, matchesij]
        S, inliers = rn.ransac_similarity(ipi, ipm)
        num_matches[i,j]=np.sum(inliers)
        ipic=ipi[:, inliers]
        ipmc=ipm[:, inliers]
        matches[i][j]=np.concatenate((ipic,ipmc),0)

        if (self.params['draw_matches']):
          imi = images[i]
          imj = images[j]
          interest_point.draw_matches_file(imi, imj, ipi, ipm, self.params['results_dir']+'/match_raw_'+str(i)+str(j)+'.jpg')
          interest_point.draw_matches_file(imi, imj, ipic, ipmc, self.params['results_dir']+'/match_'+str(i)+str(j)+'.jpg')

    t1=time()
    print(' % .2f secs' % (t1-t0))

    return matches, num_matches
