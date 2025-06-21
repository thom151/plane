# 🧮 3D Vector & Matrix Visualizer

This OpenGL-based application provides an interactive 3D environment for visualizing vector addition and matrix transformations. Users can define vectors and 4×4 matrices, view real-time vector addition, and apply transformations like **rotation**, **scaling**, **shearing**, and **translation** to both vectors and entire coordinate grids.

## 🚀 Features

- **Vector Addition Visualization**

  - Draws all user-defined vectors from the origin.
  - Displays chained vector addition steps.
  - Highlights the final resultant vector in red.

- **Matrix Multiplication & Transformation**

  - Create multiple 4×4 matrices and select multiplication order.
  - Apply matrix result to a vector or transform the entire 3D grid.
  - Supports combined transforms: scale, rotate, translate, shear.

- **Live Grid Comparison**

  - Toggle between original and transformed grid.
  - Visually compare how the plane changes under transformations.

- **ImGui Interface**

  - Edit vectors and matrix values in real-time.
  - Add/remove vectors and matrices.
  - Enable/disable grid planes (XZ, YZ).

---

## 💾 Screenshots
**Creating Vectors**
![Vectors](vectors.png)

**Adding Vectors:**
Adding multiple vectors & traces the path.
![Adding](add.png)

**Applying Matrices**
![Multiply ](multiply.png)

---

## 🛠️ Build Instructions

### Requirements

- Visual Studio 2019 or later
- OpenGL development environment set up
- Dependencies included in the project:
  - **GLFW**
  - **GLAD**
  - **GLM**
  - **ImGui**

### Steps

1. Clone or download this repository.
2. Open the solution or `.vcxproj` file in **Visual Studio**.
3. Make sure the necessary dependencies (GLFW, GLAD, etc.) are properly included and linked.
4. Build and run the project (`F5`).

> 💡 **Note:** This project assumes you already have OpenGL and its dependencies set up in Visual Studio. If not, you’ll need to manually include the libraries and headers.

---

## 🧠 Design Notes

- All vector inputs and outputs are scaled by `10x` for readability.
- Only the **translation components** (4th column of the matrix) are divided by `10` to match the grid scale.
- Vector operations are rendered using arrow lines; matrix transformations apply to a separate, cloneable grid instance.
- In Linear Algebra, matrix multiplication is not commutative — the order in which you add vectors or multiply matrices (clicking checkboxes) will affect the result.

---

## ✅ TODO / Future Work

There's still a lot of room for improvement — especially in the design and code structure. Here are my future plans:

- Add support for orthographic and perspective camera controls.
- Add preset transformations (e.g., rotate 90°, scale ×2).
- Export/import matrix and vector configurations.
- Add smooth transformation animations.
- Show numeric labels along the grid lines.
- Allow dynamic grid resizing.
- Enable trigonometric ratio inputs.
- Add dot product and cross product visualization.

---

## 🤝 Contributing

Contributions are welcome! If you'd like to improve features, fix bugs, or suggest enhancements:

1. **Fork** the repository.
2. **Clone** your fork:
   ```bash
   git clone https://github.com/yourusername/vector-matrix-visualizer.git
   ```
3. **Create a branch**:
   ```bash
   git checkout -b your-feature-name
   ```
4. Make your changes and **commit**:
   ```bash
   git commit -m "Add: your description"
   ```
5. **Push** to your fork:
   ```bash
   git push origin your-feature-name
   ```
6. **Submit a pull request** and describe your changes clearly.

Please follow consistent code style and comment major changes. If your contribution affects the UI or logic, include a short demo or screenshot if possible.

___

## 🙏 Acknowledgments

- This project was inspired by 3blue1brown's mind-opening series [Essence of Linear Algebra](https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab).

---
## 📄 License

MIT License — see `LICENSE` file.

