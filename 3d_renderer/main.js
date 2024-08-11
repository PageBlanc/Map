/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:50:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/08/11 15:01:05 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({
	antialias: true
});
const controls = new OrbitControls(camera, renderer.domElement);

camera.position.set(0, 4, 5);
controls.update();

function	animate()
{
	controls.update();
	renderer.render(scene, camera);
}

function	main() 
{
	renderer.setSize(window.innerWidth, window.innerHeight);
	document.body.appendChild(renderer.domElement);
	renderer.setAnimationLoop(animate);

	const geometry = new THREE.BufferGeometry();

	const vertices = new Float32Array([
		0.0,  1.0,  0.0,  // Sommet 1
		-1.0, -1.0,  0.0,  // Sommet 2
		1.0, -1.0,  0.0   // Sommet 3
	]);
	geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
	scene.add(new THREE.Mesh(geometry, new THREE.MeshBasicMaterial({color: 0xff0000, side: THREE.DoubleSide})));

}


main();