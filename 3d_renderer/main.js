/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:50:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/08/11 16:13:24 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import * as THREE from 'three';


const	dataMap = [
	"WWWWWWWWWPPPWWW",
	"WWWWWWPPPPPPPWW",
	"WWWWWPPPPPPPWWW",
	"WWWWPPPPPPPPWWW",
	"WWWPPPPPPPPPWWW",
	"WWWPPPPPPPPPPWW",
	"WWWPPPPPPPPPPPW",
	"WWWPPPPPPPPPPPW",
	"WWWPPPPPPPPPPPW",
	"WWWPPPPPPPPPPWW",
	"WWWPPPPPPPPPWWW",
	"WWWWPPPPPPPWWWW",
	"WWWWWPPPPPWWWWW",
	"WWWWWWPPPWWWWWW"
]


function	parseMapWaterFunc(dataMap)
{
	let vertices = [];
	let x = 0;
	let z = 0;
	for (let i = 0; i < dataMap.length; i++)
	{
		for (let j = 0; j < dataMap[i].length; j++)
		{
			if (dataMap[i][j] === 'W')
			{
				vertices.push(x, 0, z);
				vertices.push(x + 1, 0, z);
				vertices.push(x + 1, 0, z + 1);
				vertices.push(x, 0, z);
				vertices.push(x + 1, 0, z + 1);
				vertices.push(x, 0, z + 1);
			}
			x++;
		}
		x = 0;
		z++;
	}
	return vertices;
}

function	parseMapPlainFunc(dataMap)
{
	let vertices = [];
	let x = 0;
	let z = 0;

	for (let i = 0; i < dataMap.length; i++)
	{
		for (let j = 0; j < dataMap[i].length; j++)
		{
			if (dataMap[i][j] === 'P')
			{
				// if (j > 0 && dataMap[i][j - 1] === 'W')
					vertices.push(x, 1, z);
				// else
				// 	vertices.push(x, 1, z);
				vertices.push(x + 1, 1, z);
				vertices.push(x + 1, 1, z + 1);
				vertices.push(x, 1, z);
				vertices.push(x + 1, 1, z + 1);
				vertices.push(x, 1, z + 1);
			}
			x++;
		}
		x = 0;
		z++;
	}
	return vertices;
}

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({
	antialias: true
});
const controls = new OrbitControls(camera, renderer.domElement);

camera.position.set(0, 4, 5);
controls.update();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);
renderer.setAnimationLoop(animate);


const geometry = new THREE.BufferGeometry();
const parseMapWater = parseMapWaterFunc(dataMap);
const vertices = new Float32Array(parseMapWater);
geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
const Mesh = new THREE.Mesh(geometry, new THREE.MeshBasicMaterial({color: 0x0000ff, side: THREE.DoubleSide}));
Mesh.position.x = -(dataMap[0].length / 2);
Mesh.position.z = -(dataMap.length / 2);
scene.add(Mesh);

const geometry2 = new THREE.BufferGeometry();
const parseMapPlanes = parseMapPlainFunc(dataMap);
const vertices2 = new Float32Array(parseMapPlanes);
geometry2.setAttribute('position', new THREE.BufferAttribute(vertices2, 3));
const Mesh2 = new THREE.Mesh(geometry2, new THREE.MeshBasicMaterial({color: 0x00ff00, side: THREE.DoubleSide}));
Mesh2.position.x = -(dataMap[0].length / 2);
Mesh2.position.z = -(dataMap.length / 2);
scene.add(Mesh2);

function	animate()
{
	controls.update();
	renderer.render(scene, camera);
}
