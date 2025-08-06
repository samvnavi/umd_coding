for i in range(len(poly)):
    mask = np.zeros_like(cv_bgr, dtype=np.uint8)

    cv2.drawContours(mask, poly, i, (255, 255, 255), thickness=cv2.FILLED)

    contour_pixels = cv2.findNonZero(mask)

    if contour_pixels is not None:
        for pixel in contour_pixels:
            x, y = pixel[0]
            pixel_value = cv_bgr[y, x]
            print(f"Pixel at ({x}, {y}) has value {pixel_value}")
    else:
        print("No pixels found inside the contour.")
