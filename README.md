# 3-DOF Teleoperated Robotic Manipulator

This project is a 3-DOF robotic manipulator built to test real-time teleoperation, multi-axis stepper control, and serve as a foundation for vision-based manipulation.  
It is being developed collaboratively with a peer.

The arm consists of:
- **Turntable:** Bevel gear driven rotating base  
- **Shoulder:** Planetary gearbox for higher torque  
- **Elbow:** Lead screw mechanism for controlled motion  

The system is designed with **computer vision integration in mind**, as perception will play a major role in future autonomous grasping.

---

## Media

<p align="center">
  <img src="images/1.JPG" width="400">
  <img src="images/2.JPG" width="400">
</p>

**Demo Video:**  
<p align="center">
  <a href="images/3.MOV">
    [Watch Here]
  </a>
</p>

---

## Control

A Python teleoperation script sends serial commands to an Arduino that drives the motors.

**Keybindings**
- Left / Right Arrow → Turntable  
- Up / Down Arrow → Shoulder  
- W / S → Elbow  

Motion continues while the key is held and stops when released.

---

## Hardware

- Arduino controller  
- **3 NEMA 23 stepper motors**  
- **TB6600 stepper drivers**  
- Planetary gearbox (shoulder)  
- Lead screw drive (elbow)  
- Bevel gear turntable  

Planned next steps include adding a gripper and integrating vision for object detection and grasping.
