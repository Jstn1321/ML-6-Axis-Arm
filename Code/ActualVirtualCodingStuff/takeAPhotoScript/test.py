import pygame
import pygame.camera
import cv2

pygame.init()
pygame.camera.init()
camlist = pygame.camera.list_cameras()

print("Available cameras:", camlist)
