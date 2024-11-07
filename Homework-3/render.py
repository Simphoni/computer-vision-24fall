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

import numpy as np
import skimage.transform
from scipy.ndimage import map_coordinates
import im_util

def pairwise_warp(im1,im2,H):
  """
  Warp im1 to im2 coords and vice versa
  """
  # skimage transforms assume c,r rather than r,c
  P=np.zeros((3,3))
  P[0,1]=P[1,0]=P[2,2]=1

  HP=np.dot(np.dot(P,H),P)
  HPinv=np.linalg.inv(HP)

  im1_w = skimage.transform.warp(im1,skimage.transform.ProjectiveTransform(HPinv))
  im2_w = skimage.transform.warp(im2,skimage.transform.ProjectiveTransform(HP))

  return im1_w, im2_w

def pairwise_warp_file(im1,im2,H,results_prefix):
  """
  Warp im1 to im2 coords and vice versa
  """
  im1_w,im2_w = pairwise_warp(im1,im2,H)
  im_util.image_save(0.5*(im1+im2_w), results_prefix+'_im1.jpg')
  im_util.image_save(0.5*(im2+im1_w), results_prefix+'_im2.jpg')

def render_spherical(images, P_matrices, params={}):
  """
  Render images with given projection matrices in spherical coordinates
  """
  params.setdefault('theta_min', -45)
  params.setdefault('theta_max', 45)
  params.setdefault('phi_min', -30)
  params.setdefault('phi_max', 30)
  params.setdefault('render_width', 800)

  theta_min=params['theta_min'] * np.pi/180
  theta_max=params['theta_max'] * np.pi/180
  phi_min=params['phi_min'] * np.pi/180
  phi_max=params['phi_max'] * np.pi/180

  render_width=params['render_width']
  render_height=int(render_width*(phi_max-phi_min)/(theta_max-theta_min))

  world_coords=np.zeros((render_height, render_width, 3))

  theta=np.linspace(theta_min, theta_max, render_width)
  phi=np.linspace(phi_max, phi_min, render_height)

  cos_phi=np.expand_dims(np.cos(phi),1)
  sin_phi=np.expand_dims(np.sin(phi),1)
  cos_theta=np.expand_dims(np.cos(theta),0)
  sin_theta=np.expand_dims(np.sin(theta),0)

  X=np.dot(cos_phi, sin_theta)
  Y=-np.dot(sin_phi, np.ones((1,render_width)))
  Z=np.dot(cos_phi, cos_theta)

  world_coords[:, :, 0]=X
  world_coords[:, :, 1]=Y
  world_coords[:, :, 2]=Z
  wc=np.expand_dims(world_coords,2)

  pano_im=np.zeros((render_height, render_width, 4))
  im_coords=np.zeros((3,render_height, render_width,4))

  for im,P in zip(images,P_matrices):
    # compute coordinates u ~ P [X Y Z]
    uh=np.dot(wc,P.T)
    uh=uh[:, :, 0, :]
    uh=uh/np.expand_dims(uh[:, :, 2],2)

    for b in range(4):
      im_coords[0,:,:,b]=uh[:, :, 0]
      im_coords[1,:,:,b]=uh[:, :, 1]
      im_coords[2,:,:,b]=b

    # add alpha channel
    H,W,_=im.shape
    ima=np.concatenate((im,np.ones((H,W,1))),2)
    pano_im += map_coordinates(ima, im_coords, order=1)

  pano_im=pano_im / np.expand_dims((pano_im[:,:,3]+1e-6),2)
  pano_im = pano_im[:,:,0:3]

  return pano_im
