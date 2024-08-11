/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:50:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/08/11 17:52:56 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import * as THREE from 'three';
import Background from 'three/src/renderers/common/Background.js';


const	dataMap = [
	[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,0,0,3,2,0,3,3,4,0,2,0,0,0,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,0,2,0,9,8,12,13,8,19,11,2,4,0,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,4,1,8,18,12,13,10,10,13,10,11,0,0,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,0,13,14,7,12,14,6,16,19,8,5,11,0,3,0,0,0,0,0,0,0],
	[0,0,0,0,3,4,4,0,1,15,12,18,10,14,19,6,5,6,5,16,18,19,0,4,0,0,0,0,0,0],
	[0,0,0,2,0,13,17,8,18,6,15,19,13,13,16,12,16,15,10,18,19,8,14,0,2,0,0,0,0,0],
	[0,0,0,1,8,14,12,18,7,15,8,8,9,11,19,13,9,19,18,17,10,13,11,8,3,1,0,0,0,0],
	[0,0,0,1,19,16,13,7,11,9,14,10,17,5,7,17,19,6,16,17,18,9,19,9,13,4,4,0,0,0],
	[0,0,0,2,18,10,9,12,6,17,17,7,18,5,17,5,16,15,9,7,9,9,11,17,16,12,4,0,0,0],
	[0,0,0,3,12,15,8,14,9,8,19,13,14,11,11,19,17,18,17,5,5,9,6,6,11,9,10,0,0,0],
	[0,0,0,1,2,19,8,11,12,9,13,15,5,13,6,12,8,8,16,15,19,18,14,18,17,16,17,3,0,0],
	[0,0,0,0,4,12,11,18,16,17,6,7,9,9,8,19,8,11,14,18,8,6,7,17,7,16,13,2,0,0],
	[0,0,0,0,3,10,17,14,11,13,14,11,12,9,6,17,7,6,7,10,14,9,12,9,17,9,18,2,0,0],
	[0,0,0,0,2,0,5,5,7,7,5,14,19,17,15,16,16,17,5,16,5,18,5,18,11,19,15,0,0,0],
	[0,0,0,0,0,1,4,18,10,19,13,10,13,9,8,13,13,7,6,16,9,15,16,19,12,9,5,2,0,0],
	[0,0,0,0,0,0,1,12,9,16,18,11,11,9,6,13,17,8,15,7,19,18,16,15,13,8,8,4,0,0],
	[0,0,0,0,0,0,4,2,7,19,12,7,7,16,14,16,19,11,13,5,17,8,17,6,7,6,13,2,0,0],
	[0,0,0,0,0,0,0,2,19,8,18,14,10,17,13,6,5,10,6,9,13,19,14,13,5,5,0,1,0,0],
	[0,0,0,0,0,0,0,2,15,15,12,19,17,13,6,14,14,9,16,13,7,17,18,7,7,0,3,0,0,0],
	[0,0,0,0,0,0,0,0,16,11,13,6,8,12,6,8,11,11,12,12,17,5,19,12,2,1,0,0,0,0],
	[0,0,0,0,0,0,0,1,0,13,15,13,6,13,14,6,16,9,11,11,17,15,17,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,15,9,19,13,16,13,18,14,5,9,19,19,0,2,2,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,3,5,16,13,6,7,18,5,16,19,9,14,14,2,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,10,10,9,19,12,18,11,12,9,19,6,13,2,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,13,18,17,6,8,7,16,9,19,15,11,8,4,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,4,12,17,19,6,12,18,6,10,10,15,10,18,0,0,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,3,9,19,15,11,15,15,14,13,7,16,18,4,4,0,0,0,0,0,0,0,0],
]

// const	dataMap = [
// 	[0,0,0,0],
// 	[0,1,1,0],
// 	[0,1,1,0],
// 	[0,0,0,0],
// ]

let	listMesh = [];
// const	dataMap = [
// 	[0,0,0],
// 	[0,1,0],
// 	[0,0,0],
// ]

function	parseMapFunc(dataMap)
{
	let Mesh = [];

	for (let i = 0; i < dataMap.length; i++)
	{
		for (let j = 0; j < dataMap[i].length; j++)
		{
			let geometry = new THREE.BoxGeometry(1, dataMap[i][j] ? 1 : 0, 1); // (1, dataMap[i][j], 1);
			let material = new THREE.MeshPhysicalMaterial();
			Mesh = new THREE.Mesh(geometry, material);
			Mesh.castShadow = true;
			Mesh.receiveShadow = true;
			listMesh.push(Mesh);
		}
	}
}

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({
	antialias: true,
});
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.PCFSoftShadowMap;

const ambientLight = new THREE.AmbientLight(0xffffff, 0.2);
scene.add(ambientLight);

const spotLight = new THREE.SpotLight(0xffffff);
const helper = new THREE.CameraHelper(spotLight.shadow.camera);
scene.add(helper);
spotLight.position.set(100, 100, 100);
spotLight.castShadow = true;
spotLight.intensity = 25000;
spotLight.shadow.mapSize.width = 1024;
spotLight.shadow.mapSize.height = 1024;
spotLight.shadow.camera.near = 0.5;
spotLight.shadow.camera.far = 10000;
spotLight.shadow.camera.fov = 80;
scene.add(spotLight);

scene.background = new THREE.Color(0xAAAAAA);
const controls = new OrbitControls(camera, renderer.domElement);

camera.position.set(0, 4, 5);
controls.update();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);
renderer.setAnimationLoop(animate);

const geometry = new THREE.BufferGeometry();
parseMapFunc(dataMap);
for (let i = 0; i < listMesh.length; i++)
{
	listMesh[i].position.x = (i % dataMap[0].length) - dataMap[0].length / 2;
	listMesh[i].position.z = (Math.floor(i / dataMap[0].length)) - dataMap.length / 2;
	listMesh[i].position.y = listMesh[i].geometry.parameters.height / 2;
	if (listMesh[i].geometry.parameters.height != 0)
		listMesh[i].material.color.set(0xffDD00);
	if (i == 308)
	{
		listMesh[i] = new THREE.Mesh(new THREE.BoxGeometry(1, 10, 1), new THREE.MeshPhysicalMaterial());
		listMesh[i].position.x = (i % dataMap[0].length) - dataMap[0].length / 2;
		listMesh[i].position.z = (Math.floor(i / dataMap[0].length)) - dataMap.length / 2;
		listMesh[i].position.y = 1;
		listMesh[i].material.color.set(0xff0000);
		listMesh[i].castShadow = true;
		listMesh[i].receiveShadow = true;

	}
	scene.add(listMesh[i]);
}

function	animate()
{
	controls.update();
	renderer.render(scene, camera);
}
