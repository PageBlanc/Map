/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pageblanche <pageblanche@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:50:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/08/13 15:51:01 by pageblanche      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import * as THREE from 'three';
import Background from 'three/src/renderers/common/Background.js';

//const	dataMap = fs.readFileSync('map.txt', 'utf8').split('\n').map((line) => line.split(' ').map((x) => parseInt(x)));

let i = 0;

let dataMap = fetch('out.txt').then(response => response.text()).then(text => {
	let newDataMap = text.split('\n')
	dataMap = [];
	while (i < newDataMap.length)
	{
		dataMap.push(newDataMap[i].split(','));
		i++;
	}
	console.log(dataMap);
	let	listMesh = [];

	function	parseMapFunc(dataMap)
	{
		let Mesh = [];

		for (let i = 0; i < dataMap.length; i++)
		{
			for (let j = 0; j < dataMap[i].length; j++)
			{
				let geometry = new THREE.BoxGeometry(1, dataMap[i][j], 1); // (1, dataMap[i][j], 1);
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
		/*
		if (i == 308)
		{
			listMesh[i] = new THREE.Mesh(new THREE.BoxGeometry(1, 10, 1), new THREE.MeshPhysicalMaterial());
			listMesh[i].position.x = (i % dataMap[0].length) - dataMap[0].length / 2;
			listMesh[i].position.z = (Math.floor(i / dataMap[0].length)) - dataMap.length / 2;
			listMesh[i].position.y = 1;
			listMesh[i].material.color.set(0xff0000);
			listMesh[i].castShadow = true;
			listMesh[i].receiveShadow = true;

		}*/
		scene.add(listMesh[i]);
	}

	function	animate()
	{
		controls.update();
		renderer.render(scene, camera);
	}

});



